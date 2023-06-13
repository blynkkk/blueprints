// *** MAIN SETTINGS ***
// Replace this block with correct template settings. You can find it for every template here:
// https://blynk.cloud/dashboard/templates

#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"
#define BLYNK_AUTH_TOKEN "YourAuthToken"
char ssid[] = "YourNetworkName";  // Your WiFi network name
char pass[] = "YourPassword";     // Your WiFi password. Set password to "" for open networks.

// *********************

//Including the required libraries
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>  // Search for "Adafruit unified sensor" in libraries and install it
#include <Adafruit_BMP280.h>  // Search for "Adafruit BMP280" in libraries and install it
#include <BlynkSimpleEsp32.h> // Search for "Blynk" in libraries and install latest version
#include <DHT.h>              // Search for "DHT sensor library" in libraries and install it

#define BLYNK_PRINT Serial  // Comment this out to disable serial monitor prints

// DHT sensor settings 
#define DHTPIN 25
#define DHTTYPE DHT21 
DHT dht(DHTPIN, DHTTYPE);

int DHT_ENABLED = 0;
float DHT_HUMIDITY;
float DHT_HUMIDITY_IGNORED_DELTA = 0.0001;
float DHT_TEMPERATURE;
float DHT_TEMPERATURE_IGNORED_DELTA = 0.0001;

// BMP280 sensor settings
#define BMP_SCK  (18)
#define BMP_MISO (19)
#define BMP_MOSI (23)
#define BMP_CS   (5)

Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

int BMP_ENABLED = 0;
float BMP_ALTITUDE;
float BMP_PRESSURE;
float BMP_PRESSURE_IGNORED_DELTA = 0.01;
float BMP_ALTITUDE_IGNORED_DELTA = 0.01;

#define ALTITUDE_0 (1013.25)

// Blynk Datastreams definition
#define DHT_BLYNK_VPIN_TEMPERATURE V0 // temperature
#define DHT_BLYNK_VPIN_HUMIDITY V1    // humidity
#define BMP_BLYNK_VPIN_PRESSURE V4    // pressure
#define BMP_BLYNK_VPIN_ALTITUDE V3    // altitude

int RUN = 0;


//Starting DHT method
void setupDht() {
  Serial.println("DHT startup!");
  dht.begin();
  DHT_ENABLED = 1;
}
//Starting BMP method
void setupBMP() {
  Wire.begin();
  unsigned status;
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
  } else {
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    Serial.println(F("Valid BMP280 sensor"));
  }
}
//Sending data from DHT sensor to Blynk
void sendDhtData() {
  Serial.println("Sending DHT data");
  Blynk.virtualWrite(DHT_BLYNK_VPIN_TEMPERATURE, DHT_TEMPERATURE);
  Blynk.virtualWrite(DHT_BLYNK_VPIN_HUMIDITY, DHT_HUMIDITY);
}
//Sending data from BMP sensor to Blynk
void sendBMPData() {
  Serial.println("Sending BMP data");
  Blynk.virtualWrite(BMP_BLYNK_VPIN_PRESSURE, BMP_PRESSURE);
  Blynk.virtualWrite(BMP_BLYNK_VPIN_ALTITUDE, BMP_ALTITUDE);
}

// DATA PROCESSING BLOCK
//Reading DHT data
void readAndSendDhtData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT");
  } else {
    float humidityDelta = abs(humidity - DHT_HUMIDITY) - DHT_HUMIDITY_IGNORED_DELTA;
    float temperatureDelta = abs(temperature - DHT_TEMPERATURE) - DHT_HUMIDITY_IGNORED_DELTA;
    if (humidityDelta > 0 || temperatureDelta > 0) {
      DHT_HUMIDITY = humidity;
      DHT_TEMPERATURE = temperature;
      Serial.printf("Humidity: %f%%. Temperature: %f*C.\n", humidity, temperature);
      sendDhtData();
    }
  }
}
//Reading BMP data
void readBMPData() {
  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(ALTITUDE_0);
   Serial.printf("Pressure = %fhPa; Approx. Altitude = %fm;\n", pressure, altitude);

  float pressureDelta = abs(pressure - BMP_PRESSURE) - BMP_PRESSURE_IGNORED_DELTA;
  float altitudeDelta = abs(altitude - BMP_ALTITUDE) - BMP_ALTITUDE_IGNORED_DELTA;

  if (pressureDelta > 0 || altitudeDelta > 0) {
      BMP_PRESSURE = pressure;
      BMP_ALTITUDE = altitude;
      Serial.printf("Pressure = %fhPa; Approx. Altitude = %fm;\n", pressure, altitude);
      sendBMPData();
  }
  delay(500);
}
//Setup block
void setup() {
  // Debug console
  Serial.begin(115200); // Make sure you have the same baud rate in your serial monitor set up
  setupDht();
  setupBMP();
  Serial.println("Blynk setup start");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Setup is finished"); // Starting Blynk on device with AuthToken and WiFi credentials
}
//Loop block
void loop() {
  Blynk.run();  // Blynk magic happens here
  readAndSendDhtData();
  readBMPData();
  delay(50);
}
