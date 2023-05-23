#define BLYNK_PRINT Serial



#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#define BLYNK_TEMPLATE_ID "TMPL8VzQtD47K"
#define BLYNK_TEMPLATE_NAME "Blinking build in LED using Arduino UNO board"
#define BLYNK_AUTH_TOKEN "90R6egsWBn4yBOIEycCO6vCtquutfH_3"


#define LED_PIN 13

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  // Debug console
  Serial.begin(9600);

  
  //Blynk.begin(BLYNK_AUTH_TOKEN);
  // You can also specify server:
  Blynk.begin(BLYNK_AUTH_TOKEN, "fra.blynk-qa.com", 80);
  Serial.println("Blynk startup!");
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
