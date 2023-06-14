
#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h> //You need to add it by searching "Ethernet" in libraries and inslall it to this project
#include <BlynkSimpleEthernet.h> //You need to add it by searching "Blynk" in libraries and inslall it to this project

#define LED_PIN 13

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0)
{
  int value = param.asInt();

  if (value == 1)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}
