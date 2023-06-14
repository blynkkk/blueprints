/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#include <Arduino.h>

//Adding the required libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h> //You need to add it by searching "Adafruit unified sensor" in libraries and add it to this project
#include <Adafruit_BMP280.h> //You need to add it by searching "Adafruit BMP280" in libraries and add it to this project
#include <DHT.h> //You need to add it by searching "DHT sensor library" in libraries and add it to this project

// BLYNK
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"      // TemplateID can be found in Console -> Templates -> Template 
#define BLYNK_TEMPLATE_NAME "Template Name" // Template Name can be found in Console -> Templates -> Template

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"

//DHT sensor settings and configuration
#define DHT_BLYNK_VPIN_TEMPERATURE V0 //Virtual pin on Blynk side
#define DHT_BLYNK_VPIN_HUMIDITY V1 //Virtual pin on Blynk side

#define DHTPIN 25
#define DHTTYPE DHT21 
DHT dht(DHTPIN, DHTTYPE);


// BMP sensor settings and configuration
#define BMP_BLYNK_VPIN_PRESSURE V4 //Virtual pin on Blynk side
#define BMP_BLYNK_VPIN_ALTITUDE V3 //Virtual pin on Blynk side

#define BMP_SCK  (18)
#define BMP_MISO (19)
#define BMP_MOSI (23)
#define BMP_CS   (5)
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

#define ALTITUDE_0 (1013.25)


// This function creates the timer object. It's part of Blynk library 
BlynkTimer timer; 

// DHT related variables
int   DHT_ENABLED = 0;
float DHT_HUMIDITY;
float DHT_HUMIDITY_IGNORED_DELTA = 0.01;
float DHT_TEMPERATURE;
float DHT_TEMPERATURE_IGNORED_DELTA = 0.01;

// BMP related variables

int   BMP_ENABLED = 0;
float BMP_ALTITUDE;
float BMP_PRESSURE;
float BMP_PRESSURE_IGNORED_DELTA = 0.01;
float BMP_ALTITUDE_IGNORED_DELTA = 0.01;

int RUN = 0;


// SETUP BLOCK

//DHT setup
void setupDht() {
  Serial.println("DHT startup!");
  dht.begin();
  DHT_ENABLED = 1;
}
// BMP setup
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
void readAndSendBMPData() {
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

}
void reandAndSendSensorsData() {
  readAndSendBMPData();
  readAndSendDhtData();
  Serial.println("Sending data from sensors");
}

void setup()
{
  Serial.begin(115200);
  BlynkEdgent.begin();
  setupDht();
  setupBMP();
  timer.setInterval(5000L, reandAndSendSensorsData); //timer will run every 5 sec

}

void loop() {
  Blynk.run();  
  timer.run();
}

