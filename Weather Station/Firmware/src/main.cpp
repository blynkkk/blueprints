#include <Arduino.h>

//Connecting sensors
// BME
// 1 VCC -> 3.3V
// 2 GND -> GND
// 3 SCL -> 18
// 4 SDA -> 23
// 5 CSB -> 5
// 6 SDO -> 19


// DHT
// RED    -> 3.3V
// BLACK  -> GND
// YELLOW -> 25

//Adding the required libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// BLYNK
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "*******"
#define BLYNK_TEMPLATE_NAME "********"
#define BLYNK_AUTH_TOKEN "*********"

#define BLYNK_DOMAIN "blynk.cloud"
#define BLYNK_PORT 80 //443


// DHT
#define DHTPIN 25
#define DHTTYPE DHT21 

#define DHT_BLYNK_VPIN_TEMPERATURE V0
#define DHT_BLYNK_VPIN_HUMIDITY V1

//DHT sensor settings
DHT dht(DHTPIN, DHTTYPE);

int DHT_ENABLED = 0;
float DHT_HUMIDITY;
float DHT_HUMIDITY_IGNORED_DELTA = 0.0001;
float DHT_TEMPERATURE;
float DHT_TEMPERATURE_IGNORED_DELTA = 0.0001;

#define BMP_SCK  (18)
#define BMP_MISO (19)
#define BMP_MOSI (23)
#define BMP_CS   (5)

#define ALTITUDE_0 (1013.25)

#define BMP_BLYNK_VPIN_PRESSURE V4
#define BMP_BLYNK_VPIN_ALTITUDE V3

// BMP280 sensor settings;
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

int BMP_ENABLED = 0;
float BMP_ALTITUDE;
float BMP_PRESSURE;
float BMP_PRESSURE_IGNORED_DELTA = 0.01;
float BMP_ALTITUDE_IGNORED_DELTA = 0.01;

int RUN = 0;

// SETUP BLOCK
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
  Serial.begin(115200);
  setupDht();
  setupBMP();
  Serial.println("Blynk setup start");
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS, BLYNK_DOMAIN, BLYNK_PORT);
  Serial.println("Setup is finished");
}
//Loop block
void loop() {
  Blynk.run();  
  readAndSendDhtData();
  readBMPData();
  delay(50);
}
