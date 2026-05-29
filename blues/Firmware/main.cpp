#include <Arduino.h>
#include <Notecard.h>
#include <Wire.h>
#include "SparkFun_BMP581_Arduino_Library.h"

#define IS_DEBUG true
#define PRODUCT_UID "your-unique-notehub-productuid"
float LAT = 10.00000; // optionally hardcode lat/lon for a stationary deployment
float LON = -10.00000;

HardwareSerial stlinkSerial(PIN_VCP_RX, PIN_VCP_TX);
unsigned long currentMillis, startMillisSensor, startMillisDoor, startMillisAlert;
unsigned long sensorReadPeriod = 1000 * 30;    // read sensor every 30 secs, this may be updated by inbound data from Blynk
unsigned long doorReadPeriod = 1000;           // read door status every 1 sec
unsigned long doorOpenAlertPeriod = 1000 * 10; // send door ajar alert after 10 secs

Notecard notecard;
BMP581 bmp581;
uint8_t bmpi2c = BMP581_I2C_ADDRESS_DEFAULT; // 0x47

const int REED_PIN = 5; // Pin connected to reed switch

// all the values from our sensors etc
float voltage = 0.0;
float temperature = 0.0;
int pressure = 0;
int bars = 0;
bool door_open = false;
bool alert_sent = false;

void updateSensorCadence();

void setup()
{
#ifdef IS_DEBUG
  stlinkSerial.begin(115200);
  const size_t usb_timeout_ms = 3000;
  for (const size_t start_ms = millis(); !stlinkSerial && (millis() - start_ms) < usb_timeout_ms;)
    ;
  notecard.setDebugOutputStream(stlinkSerial);
#endif

  Wire.begin();
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  // #######################
  // initialize the Notecard
  // #######################

  // init notecard and notehub
  notecard.begin();

  J *req = notecard.newRequest("hub.set");
  if (req != NULL)
  {
    JAddStringToObject(req, "product", PRODUCT_UID);
    JAddStringToObject(req, "mode", "continuous");
    JAddBoolToObject(req, "sync", true);
    JAddStringToObject(req, "sn", "Cellular Fridge"); // optional identifier: Cellular Fridge, LoRa Fridge, Wi-Fi Fridge
    notecard.sendRequestWithRetry(req, 5);
  }

  // set wi-fi credentials (only used on Notecard WiFi)
  req = notecard.newRequest("card.wifi");
  if (req != NULL)
  {
    JAddStringToObject(req, "ssid", "your-ssid");
    JAddStringToObject(req, "password", "your-password");
    notecard.sendRequest(req);
  }

  // create a notefile template
  req = notecard.newRequest("note.template");
  if (req != NULL)
  {
    JAddStringToObject(req, "file", "fridge_sensors.qo");
    JAddNumberToObject(req, "port", 22);
    JAddStringToObject(req, "format", "compact");
    J *body = JAddObjectToObject(req, "body");
    if (body)
    {
      JAddNumberToObject(body, "voltage", 12.1);
      JAddNumberToObject(body, "temperature", 12.1);
      JAddNumberToObject(body, "pressure", 12);
      JAddNumberToObject(body, "bars", 12);
      JAddBoolToObject(body, "door_status", true);
      JAddNumberToObject(body, "_lat", 14.1);
      JAddNumberToObject(body, "_lon", 14.1);
    }
    notecard.sendRequest(req);
  }

  req = notecard.newRequest("note.template");
  if (req != NULL)
  {
    JAddStringToObject(req, "file", "fridge_alert.qo");
    JAddNumberToObject(req, "port", 23);
    JAddStringToObject(req, "format", "compact");
    J *body = JAddObjectToObject(req, "body");
    if (body)
    {
      JAddBoolToObject(body, "alert", true);
    }
    notecard.sendRequest(req);
  }

  // set a fixed gps position based on the location of the demo
  req = notecard.newRequest("card.location.mode");
  if (req != NULL)
  {
    JAddStringToObject(req, "mode", "fixed");
    JAddNumberToObject(req, "lat", LAT);
    JAddNumberToObject(req, "lon", LON);
    notecard.sendRequest(req);
  }

  // ############################
  // initialize the bmp581 sensor
  // ############################

  while (bmp581.beginI2C(bmpi2c) != BMP5_OK)
  {
#ifdef IS_DEBUG
    stlinkSerial.println("Error: BMP581 not connected, check wiring and I2C address!");
#endif
    delay(500);
  }

  startMillisSensor = millis();
  startMillisDoor = millis();
}

void loop()
{
  currentMillis = millis();

  // ################
  // read door status
  // ################

  if (currentMillis - startMillisDoor >= doorReadPeriod)
  {
    int proximity = digitalRead(REED_PIN); // Read the state of the switch

    // If the pin reads low, the switch is closed.
    if (proximity == LOW)
    {
#ifdef IS_DEBUG
      // stlinkSerial.println("door closed");
#endif
      digitalWrite(LED_BUILTIN, LOW);
      door_open = false;
      alert_sent = false; // reset the alert flag
    }
    else
    {
#ifdef IS_DEBUG
      stlinkSerial.println("door opened");
#endif
      digitalWrite(LED_BUILTIN, HIGH);
      if (!door_open)
      {
        door_open = true;
        startMillisAlert = millis();
      }
    }

    startMillisDoor = millis();
  }

  // ############################################
  // check to see if we have to send a door alert
  // ############################################

  if (door_open && !alert_sent && currentMillis - startMillisAlert >= doorOpenAlertPeriod)
  {
    J *req = notecard.newRequest("note.add");
    if (req != NULL)
    {
      JAddStringToObject(req, "file", "fridge_alert.qo");
      JAddBoolToObject(req, "sync", true);
      J *body = JAddObjectToObject(req, "body");
      if (body != NULL)
      {
        JAddBoolToObject(body, "alert", true);
      }
      notecard.sendRequest(req);
    }
    alert_sent = true;
  }

  // ################
  // read sensor data
  // ################

  if (currentMillis - startMillisSensor >= sensorReadPeriod)
  {
    // query notecard for voltage reading
    J *req = notecard.newRequest("card.voltage");
    if (req != NULL)
    {
      J *rsp = notecard.requestAndResponse(req);

      if (rsp)
      {
        voltage = JGetNumber(rsp, "value");

        if (!voltage)
        {
          voltage = 0.0;
        }

        notecard.deleteResponse(rsp);
      }
    }

    // query notecard for last cellular info
    req = notecard.newRequest("card.wireless");
    if (req != NULL)
    {
      J *rsp = notecard.requestAndResponse(req);

      if (rsp)
      {
        J *net = JGetObject(rsp, "net");

        if (net)
        {
          bars = JGetNumber(net, "bars");

          if (!bars)
          {
            bars = 0;
          }
        }

        notecard.deleteResponse(rsp);
      }
    }

    // query bmp581 for sensor readings
    bmp5_sensor_data data = {0, 0};
    int8_t err = bmp581.getSensorData(&data);

    // Check whether data was acquired successfully
    if (err == BMP5_OK)
    {
#ifdef IS_DEBUG
      // Acquisition succeeded, print temperature and pressure
      stlinkSerial.print("Temperature (C): ");
      stlinkSerial.print(data.temperature);
      stlinkSerial.print("\t\t");
      stlinkSerial.print("Pressure (Pa): ");
      stlinkSerial.println(data.pressure);
#endif

      temperature = data.temperature;
      pressure = data.pressure / 100.0;
    }
    else
    {
#ifdef IS_DEBUG
      // Acquisition failed, most likely a communication error (code -2)
      stlinkSerial.print("Error getting data from sensor! Error code: ");
      stlinkSerial.println(err);
#endif
    }

    req = notecard.newRequest("note.add");
    if (req != NULL)
    {
      JAddStringToObject(req, "file", "fridge_sensors.qo");
      JAddBoolToObject(req, "sync", true);
      J *body = JAddObjectToObject(req, "body");
      if (body != NULL)
      {
        JAddNumberToObject(body, "voltage", voltage);
        JAddNumberToObject(body, "temperature", temperature);
        JAddNumberToObject(body, "pressure", pressure);
        JAddNumberToObject(body, "bars", bars);
        JAddBoolToObject(body, "door_status", door_open);
      }
      notecard.sendRequest(req);
    }

    startMillisSensor = currentMillis;

    updateSensorCadence();
  }

  delay(100);
}

void updateSensorCadence()
{
  // check for inbound data from Blynk that will set the sensor cadence
  J *req = notecard.newRequest("file.changes");
  if (req != NULL)
  {
    J *files = JAddArrayToObject(req, "files");
    JAddItemToArray(files, JCreateString("blynk.qi"));
    J *rsp = notecard.requestAndResponse(req);

    if (rsp)
    {
      int total = JGetNumber(rsp, "total");

      if (total && total > 0)
      {
        req = NoteNewRequest("note.get");
        if (req != NULL)
        {
          JAddStringToObject(req, "file", "blynk.qi");
          JAddBoolToObject(req, "delete", true);

          rsp = notecard.requestAndResponse(req);

          if (rsp)
          {
            J *body = JGetObject(rsp, "body");

            if (body)
            {
              if (JGetNumber(body, "Sync Freq"))
              {
                sensorReadPeriod = 1000 * JGetNumber(body, "Sync Freq");
#ifdef IS_DEBUG
                stlinkSerial.print("Sync cadence updated on this device to: ");
                stlinkSerial.println(sensorReadPeriod);
#endif
              }
            }
          }
        }
      }
    }
  }
}

