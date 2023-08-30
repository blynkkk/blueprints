// *** MAIN SETTINGS ***
// Replace this block with correct template settings.
// You can find it for every template here:
//
//   https://blynk.cloud/dashboard/templates
// #define BLYNK_TEMPLATE_ID "Your_Template_ID"
// #define BLYNK_TEMPLATE_NAME "Your_Template_Name"



#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
// #define USE_ESP32_DEV_MODULE
// #define USE_ESP32C3_DEV_MODULE
// #define USE_ESP32S2_DEV_KIT
#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"

#define LED_PIN 2  // LED is usually connected to D2 pin. Change if needed.

BLYNK_WRITE(V0)
// V0 is a datastream used to transfer and store LED switch state.
// Evey time you use the LED switch in the app, this function
// will listen and update the state on device
{
  int value = param.asInt();
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:

  if (value == 1) {
    digitalWrite(LED_PIN, HIGH);
    Serial.print("value =");
    Serial.println(value);
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.print("value = ");
    Serial.println(value);
  }
}
void setup() {
  // Debug console
  Serial.begin(115200);  // Make sure you have the same baud rate in your serial monitor set up
  pinMode(LED_PIN, OUTPUT);
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  delay(100);
}
