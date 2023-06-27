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
  - Simple LVGL-based UI

  NOTE: Please update the WiFi module firmware, if needed:
    https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"


#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

void display_update_state();

#include "BlynkEdgent.h"
#include <TFT_eSPI.h>

//Blynk virtual pins
#define BLYNK_VPIN_SOIL_MOISTURE V0   //Virtual pin on Blynk side
#define BLYNK_VPIN_LIGHT V1           //Virtual pin on Blynk side

#define APP_DEBUG

//Board configuration and properties
#define WATER_SENSOR A0

//Initializations
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
TFT_eSprite spr = TFT_eSprite(&tft);


#define BLK 1

//Global variables
int soilMoisture = 0;
int light = 0;

void board_init() {
    pinMode(WIO_LIGHT, INPUT);  //WIO_LIGHT: 27
    pinMode(WIO_BUZZER, OUTPUT);  //WIO_BUZZER: 12
    pinMode(BLK, OUTPUT); //backlight control
    analogWrite(BLK, 255);

    tft.begin();
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_WHITE);
}

void beep() {
    analogWrite(WIO_BUZZER, 150); //beep the buzzer
    delay(100);
    analogWrite(WIO_BUZZER, 0); //Silence the buzzer
    delay(1000);
}

void refreshScreen() {
  //Setting the title header 
  tft.fillRect(0, 0, TFT_HEIGHT, 60, TFT_DARKGREEN); //Rectangle fill with dark green 
  tft.setTextColor(TFT_WHITE); //Setting text color
  tft.setTextSize(3); //Setting text size 
  tft.drawString("Garden Monitor", 40, 10);
  tft.setTextSize(2);
  tft.drawString("@blynk", 240,40); //Drawing a text string 

  //Condition for low soil moisture
  if (soilMoisture < 50) {
    tft.fillRect(0, 60, TFT_HEIGHT, TFT_WIDTH, TFT_RED);
    tft.drawString("Time to water!", 35,100);
    // beep(); // beeping
  } else {
    tft.fillRect(0, 60, TFT_HEIGHT, TFT_WIDTH, TFT_WHITE);
    tft.drawFastHLine(0, 145, 320, TFT_DARKGREY); //Drawing horizontal line
    
    tft.setTextSize(3);
    tft.setTextColor(TFT_DARKGREY); //Setting text color to dark since background is white
    
    //Setting soil moisture
    tft.drawString("Soil", 25, 80);
    tft.drawString("Moisture", 25, 110);
    tft.drawNumber(soilMoisture, 200, 95); //Display sensor values as percentage  
    tft.drawString("%", 240, 95);
 
    //Setting light 
    tft.setTextSize(3);
    tft.drawString("Light", 25, 180);
    tft.drawNumber(light, 205, 180); //Display sensor values as percentage  
    tft.drawString("%", 245, 180);
  }
  
  delay(50);
}


void sendDataToBlynk() {

  Serial.println("Sending Data to Blynk");
  Blynk.virtualWrite(BLYNK_VPIN_SOIL_MOISTURE, soilMoisture);
  Blynk.virtualWrite(BLYNK_VPIN_LIGHT, light);
}

void readDataFromSensors() {
  int waterSensorValue = analogRead(WATER_SENSOR);
  int lightSensorValue = analogRead(WIO_LIGHT);

  soilMoisture = map(waterSensorValue, 1023,0 ,0, 100); //Map sensor values 
  light = map(lightSensorValue, 0, 1023, 0, 100); //Map sensor values 
  Serial.printf("soilMoisture: %d light: %d \n", soilMoisture, light);
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  board_init(); 

  edgentTimer.setInterval(5000L, sendDataToBlynk); 
  edgentTimer.setInterval(1000, []() {
    readDataFromSensors();
    refreshScreen();
  });

  BlynkEdgent.begin();

  beep(); // Beep once when it starts
}

void loop()
{
  BlynkEdgent.run();
}