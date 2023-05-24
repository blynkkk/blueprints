#define BLYNK_PRINT Serial


#include <SPI.h>
#include <Ethernet.h> //You need to add it by searching "Ethernet" in libraries and inslall it
#include <BlynkSimpleEthernet.h> //You need to add it by searching "Blynk" in libraries and inslall it

#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"


#define LED_PIN 13

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, "fra.blynk-qa.com", 80);
  //You can also use
  //Blynk.begin(BLYNK_AUTH_TOKEN);
  //Blynk.begin(BLYNK_AUTH_TOKEN, IPAddress(192,168,1,100), 8080);
  // For more options, see Boards_Ethernet/Arduino_Ethernet_Manual example
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
