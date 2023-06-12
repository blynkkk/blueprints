#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"
#define BLYNK_AUTH_TOKEN "YourAuthToken"
char ssid[] = "YourNetworkName";  // Your WiFi credentials.
char pass[] = "YourPassword";     // Set password to "" for open networks.

// Comment this out to disable prints
#define BLYNK_PRINT Serial

//Adding the required libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define LED_PIN 2 // LED is usually connected to D2 pin. Change if needed.

void setup()
{
  
  Serial.begin(115200); // Debug console. Make sure you have the same baud rate in your serial monitor set up
  pinMode(LED_PIN, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run(); // Blynk magic happens here
}



BLYNK_WRITE(V0) // V0 is a datastream used to transfer and store LED switch state
// Evey time you use the LED switch in the app, this function
// will listen and update the state on device  
  
{
  int value = param.asInt();
  // Local variable `value` will store the incoming LED switch state (1 or 0)
  // Based on the value, the physical LED on the board will be on or off
  
  if (value == 1)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}
