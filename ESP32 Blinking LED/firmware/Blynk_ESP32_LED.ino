// *** MAIN SETTINGS ***
// Replace this block with correct template settings. You can find it for every template here:
// https://blynk.cloud/dashboard/templates

#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"
#define BLYNK_AUTH_TOKEN "YourAuthToken"
char ssid[] = "YourNetworkName";  // Your WiFi network name
char pass[] = "YourPassword";     // Your WiFi password. Set password to "" for open networks.

// *********************

//Adding the required libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial  // Comment this out to disable serial monitor prints
#define LED_PIN 2           // LED is usually connected to D2 pin. Change if needed.

void setup()
{
  // Debug console
  Serial.begin(9600);                         // Make sure you have the same baud rate in your serial monitor set up
 pinMode(LED_PIN, OUTPUT);                    // Setting LED PIN to control it
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Starting Blynk on device with AuthToken and WiFi credentials
}

void loop()
{
  Blynk.run(); // Blynk magic happens here
}

BLYNK_WRITE(V0)
// V0 is a datastream used to transfer and store LED switch state.
// Evey time you use the LED switch in the app, this function
// will listen and update the state on device  
{
  int value = param.asInt();
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:

  if (value == 1)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}
