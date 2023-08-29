#include "Particle.h"
#include <math.h> // This library is only for function simulating a sensor
const char *firmware_version = "0.0.0";

double v15 = 3.14159;
uint32_t simSensor_timer_last = 0; // This is a variable for a function that simulates a sensor
uint8_t led_state = LOW;
bool particle_fn_called = TRUE; // causes the device to publish data immediately after started/boot and connected to the Particle cloud.

// Register the Particle cloud function
int blynkLED(String on_or_off);

/////////////////////////////////////////////////////////////////////////
// Blynk

// Update below with your Blynk auth token for your device (automatically populated by Blueprint)
#define BLYNK_TEMPLATE_ID "13 char template id"
#define BLYNK_TEMPLATE_NAME "ParticleDeviceBlueprint"
#define BLYNK_AUTH_TOKEN "your Blynk 32 char auth token"

void simSensor()    //This function simulates a sensor
{ 
  long sim = random(millis());
  if (millis() - simSensor_timer_last >= 20000) {
    simSensor_timer_last = millis();
    float deltaSensor = cos(float(sim) / 1000) / 100;
       if (v15 <= 0 || v15 >= 3.3)
    {
      v15 = v15 - deltaSensor;
    }
    else
    {
      v15 = v15 + deltaSensor;
     }
  }
} // simSensor

/////////////////////////////////////////////////////////////////////////

bool deviceHasLedOnD7()
{
  // Returns TRUE if the device has a built-in LED on D7:
  //  Boron, Argon, Photon 2, Photon, Electron, Core
  // 8: P1
  switch (PLATFORM_ID)
  {
  case PLATFORM_BORON:
  case PLATFORM_ARGON:
  case 0:  // Core
  case 6:  // Photon  (PLATFORM_PHOTON_PRODUCTION)
  case 10: // Electron  (PLATFORM_ELECTRON_PRODUCTION)
    return TRUE;
  default:
    return FALSE;
  }
} // deviceHasLedOnD7()

/////////////////////////////////////////////////////////////////////////
// Timer

const uint32_t TIMER_INTERVAL_MS = 300000L;
uint32_t timer_last = 0;

void pubToParticleBlynk()
{
  if (Particle.connected())
  {
    
    char data[90]; // See serial output for the actual size in bytes and adjust accordingly.
    // Note the escaped double quotes around the ""t"" for BLYNK_AUTH_TOKEN.
    snprintf(data, sizeof(data), "{\"t\":\"%s\",\"v14\":%u,\"v15\":%f,\"v16\":%u,\"v17\":%u}", BLYNK_AUTH_TOKEN, millis(), v15, led_state, led_state);
    Serial.printlnf("Sending to Blynk: '%s' with size of %u bytes", data, strlen(data));
    bool pub_result = Particle.publish("blynk_https_get", data, PRIVATE);
    if (pub_result)
    {
      timer_last = millis();
    }
    else
    {
      Serial.println("ERROR: Particle.publish()");
    }
  }
} // pubToParticleBlynk()

void pubTimer()
{
  // A timer for publishing data to Particle Cloud, and then continuing to Blynk.
  if (timer_last > millis())
    timer_last = millis();
  if ((millis() - timer_last) > TIMER_INTERVAL_MS && Particle.connected())
  {
    pubToParticleBlynk();
    timer_last = millis();
  }
} // pubTimer()

/////////////////////////////////////////////////////////////////////////

void setup()
{
  

  if (deviceHasLedOnD7() == TRUE)
  {
    pinMode(D7, OUTPUT);
    digitalWrite(D7, LOW);
  }

  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);
  delay(1000);
  Serial.printlnf("Device OS v%s", System.version().c_str());
  Serial.printlnf("Free RAM %lu bytes", System.freeMemory());
  Serial.printlnf("Firmware version v%s", firmware_version);

  // register the Particle cloud function (funcKey, funcName)
  Particle.function("blynk_led", blynkLED);

  Serial.println("Setup complete");

} // setup()

void loop()
{
  simSensor(); // This is function simulates a sensor
  pubTimer();
  

  if (particle_fn_called == TRUE)
  {
    particle_fn_called = FALSE;
    // Publish data to Particle cloud..
    pubToParticleBlynk();
  }

  if (deviceHasLedOnD7() == TRUE)
  {
    digitalWrite(D7, led_state);
  }

} // loop()

int blynkLED(String on_off)
{
  // Custom Particle cloud function that changes the state of the built-in LED
  // on D7 in response to an instruction from Blynk calling this
  // custom cloud function.
  // Returns the value 1 if the LED has been turned on, and 0 if turned off,
  // -1 if an unexpected on_off value is received.
  // Cloud functions must return int and take one String argument
  // curl https://api.particle.io/v1/devices/{your 25 char device id}/blynk_led
  // -d access_token={your 40 char access token}
  // -d "args=on/off"

  if (on_off == "on" || on_off == "1")
  {
    particle_fn_called = TRUE;
    led_state = HIGH;
    return 1;
  }
  else if (on_off == "off" || on_off == "0")
  {
    particle_fn_called = TRUE;
    led_state = LOW;
    return 0;
  }
  else
  {
    Serial.print("Unexpected on_off value of: '");
    Serial.print(on_off);
    Serial.println("'");
  }
  return -1;

} // blynkLED()
