
// *** MAIN SETTINGS ***
// Replace this block with correct template settings.
// You can find it for every template here:
//
//   https://blynk.cloud/dashboard/templates

#define BLYNK_TEMPLATE_ID     "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME   "Device"
#define BLYNK_AUTH_TOKEN      "YourAuthToken"

// Adding the required libraries
#include "Particle.h"

#include <Adafruit_GPS.h>  // Library for GPS module. You need to add it to this project

const char* firmware_version = "0.0.1";
boolean just_started = true;

// Battery and cellular signal variables (and default values)
String batt_chg = "no battery"; // battery charge
String cell_str = "N/A";        // cellular signal strength
String cell_qual = "N/A";       // cellular signal quality

// Variables related to data to be sent on boot
uint8_t just_booted = 1;
uint8_t boot_status_published = 0;

// Timers
// How often to check cellular signal and battery charge level
const uint16_t TIMER_INTERVAL_CELL_BAT_MS = 10000;
uint32_t timer_last_cell_batt_check_ms = 0;

// How often to collect cellular connection stats
const uint16_t PARTICLE_CONNECTED_WAIT = 10000;
uint32_t particle_connected_wait_ms = 0;

// How often data should be published. Default is 5 min (or 300000 ms)
const uint32_t TIMER_INTERVAL_MS = 300000;
uint32_t last_publish_ms = 0;

// Cellular signal strength, quality, and battery charge variables
float cell_sig_strength = -1.0; // -1 if unknown; 0.0 to 100.0 (larger = better)
float cell_sig_quality = -1.0; // -1 if unknown; 0.0 to 100.0 (larger = better)
float batt_charge = -1.0; // -1 if unknown; 0.0 to 100.0 (larger = better)

// GPS
// Serial1 is also UART1 on the Boron/Argon/Xenon pins D10/Rx and D9/Tx
#define SerialGPS Serial1
// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&SerialGPS);
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false

float lat = 0.0;
float lon = 0.0;
float mph = 0.0;
bool publish_to_blynk = false;
uint8_t loc = 0; // 1 when the GPS position of the device has changed by more than 122 m or 400 ft.

// Function to update cellular signal strength and battery charge
void CellBattUpdate() {
  // Wait until 10 seconds after Particle.connected() to get the cellular connection statistics
  // Thereafter, only update the cellular connection & battery charge global variables every
  // PARTICLE_CONNECTED_WAIT ms.

  if ((millis() - timer_last_cell_batt_check_ms) > TIMER_INTERVAL_CELL_BAT_MS) {

    if (Particle.connected()) {
      // Connected to the Particle cloud; typically 10001 ms
      // Below executes only once.
      if (just_booted == 1) {
        Serial.println("Just booted...");
        particle_connected_wait_ms = millis();
        just_booted = 0;
      }
    }

    if (Particle.connected() && (millis() - particle_connected_wait_ms > PARTICLE_CONNECTED_WAIT)) {

      // When 10 seconds have elapsed since Particle.connected(),
      // get the cellular connection status
      batt_charge = System.batteryCharge();
      cell_sig_strength = Cellular.RSSI().getStrength();
      cell_sig_quality = Cellular.RSSI().getQuality();

      // Converting data to strings that can be published
      batt_chg = "no battery";
      if (batt_charge >= 0.0) {
        batt_chg = String(batt_charge, 1);
      }
      cell_str = "N/A";
      if (cell_sig_strength >= 0.0) {
        cell_str = String(cell_sig_strength, 1);
      }
      cell_qual = "N/A";
      if (cell_sig_quality >= 0.0) {
        cell_qual = String(cell_sig_quality, 1);
      }

      Serial.printlnf("\nCellular signal strength: %.02f%%", cell_sig_strength);
      Serial.printlnf("Cellular signal quality: %.02f%%", cell_sig_quality);
      Serial.printlnf("System.batteryCharge(): %.02f%%\n", batt_charge);

      if (boot_status_published == 0) {
        char data[200]; // Adjust size as needed
        // Note the escaped double quotes around the value for BLYNK_AUTH_TOKEN.
        snprintf(data, sizeof(data), R"json({"t":"%s","v10":"%s","v11":"%s","v12":"%s"})json",
          BLYNK_AUTH_TOKEN,
          batt_chg.c_str(),
          cell_str.c_str(),
          cell_qual.c_str()
        );

        // Checking the complete string that will be published.
        // Make sure you don't see any special characters.
        Serial.println("Publishing on boot:");
        Serial.println(data);

        // Publishing data to Particle which will pass it to Blynk over webhook
        bool pub_result = Particle.publish("blynk_https_get_boot", data, PRIVATE);

        if (pub_result) {
          boot_status_published = 1;
          Serial.println("Published");
        } else {
          Serial.println("ERROR: Particle.publish()");
        }
      }

      particle_connected_wait_ms = millis();
    }
    timer_last_cell_batt_check_ms = millis();
  }

}

// Publish to Particle (and Blynk) only when something happens.
void publishTimer() {
  if (millis() - last_publish_ms >= TIMER_INTERVAL_MS) {

    //  Publish to Blynk if the device's position has changed by more than 122 m or 400 ft.
    publish_to_blynk = false;

    loc = 0; // location has not changed (default).

    if (GPS.fix) {
      Serial.printlnf("GPS UTC %4d-%02d-%02dT%02d:%02d:%02d%+05d, fix qual %d, sat %d, lat %0.5f, lon %0.5f, mph %0.1f, %0.1f deg, altitude %0.1f m, mag var %0.1f deg", GPS.year + 2000, GPS.month, GPS.day, GPS.hour, GPS.minute, GPS.seconds, 0, GPS.fixquality, GPS.satellites, GPS.latitudeDegrees, GPS.longitudeDegrees, GPS.speed, GPS.altitude, GPS.angle, GPS.magvariation);
      if ((int)lat == 0 || (int)lon == 0) {
        lat = GPS.latitudeDegrees;
        lon = GPS.longitudeDegrees;
        mph = GPS.speed * 1.15078; // convert the speed in knots to mph
      }

      // Simulate location change
      //lat = lat + 0.0012; // more than 400 ft
      //Serial.printlnf("Latitude/Longitude: %f, %f", lat, lon);

      // FIX:  0 means no 'valid fix', 1 means 'normal precision', and 2 means the position data is further corrected by some differential system.  Typically 1 with internal antenna, 2 with external antenna.
      // Sat:  => 4 typical, but over time in home varies from 4 to 6 with internal antenna. With external antenna, typically 8 to 10.
      // Note that knots will float at 0.1 to 1.2 when the GPS is at rest with the internal antenna.  With external antenna, value is 0.0 to 0.01 knots.
      // Lat/Lon in decimal degrees to 3 decimal places is 111 m / 364 ft, to 4 places = 11.1 m or 36.4 ft.
      // A change in GPS latitude/latitude of 0.0011 is a distance of 122 m or 400 ft.
      //if (GPS.fixquality > 0 && (fabs(GPS.latitudeDegrees - lat) > 0.001 || fabs(GPS.longitudeDegrees - lat) > 0.001)) {
      if (GPS.fixquality > 0 && (fabs(fabs(GPS.latitudeDegrees) - fabs(lat)) > 0.0011 || fabs(fabs(GPS.longitudeDegrees) - fabs(lon)) > 0.0011)) {
        double delta_lat_m = fabs(fabs(GPS.latitudeDegrees) - fabs(lat))*10000.0/90.0*1000.0;  // distance in m
        double delta_lon_m = fabs(fabs(GPS.longitudeDegrees) - fabs(lon))*10000.0/90.0*1000.0;
        double delta_lat_ft = fabs(fabs(GPS.latitudeDegrees) - fabs(lat))*10000.0/90.0*3280.4;  // distance in ft
        double delta_lon_ft = fabs(fabs(GPS.longitudeDegrees) - fabs(lon))*10000.0/90.0*3280.4;
        double delta_m = max(delta_lat_m, delta_lon_m);
        double delta_ft = max(delta_lat_ft, delta_lon_ft);
        publish_to_blynk = true;
        loc = 1;
        Serial.printlnf("The device has moved a distance of %f m or %f ft since the last time the GPS position was reported", delta_m, delta_ft);
      }
      if (GPS.fixquality > 0 && just_started == true) {
        publish_to_blynk = true;
        just_started = false;
      }
      lat = GPS.latitudeDegrees;
      lon = GPS.longitudeDegrees;
      mph = GPS.speed * 1.15078; // convert the speed in knots to mph
    } else {
      Serial.println("NO GPS fix!");
    }

    if (publish_to_blynk == true) {
      batt_chg = "no battery";
      if (batt_charge >= 0.0) {
        batt_chg = String(batt_charge, 1);
      }
      cell_str = "N/A";
      if (cell_sig_strength >= 0.0) {
        cell_str = String(cell_sig_strength, 1);
      }
      cell_qual = "N/A";
      if (cell_sig_quality >= 0.0) {
        cell_qual = String(cell_sig_quality, 1);
      }
      char data[130]; // See serial output for the actual size in bytes and adjust accordingly.
      // Note the escaped double quotes around the value for BLYNK_AUTH_TOKEN.
      snprintf(data, sizeof(data), "{\"t\":\"%s\",\"lat\":%f,\"lon\":%f,\"spd\":%f,\"moved\":%u,\"v10\":%s,\"v11\":%s,\"v12\":%s}", BLYNK_AUTH_TOKEN, lat, lon, mph, loc, batt_chg, cell_str, cell_qual);
      Serial.printlnf("Sending to Blynk: '%s' with size of %u bytes", data, strlen(data));
      bool pub_result = Particle.publish("blynk_https_get", data, PRIVATE);
      if (pub_result) {
        publish_to_blynk = false;
      } else {
        Serial.println("ERROR: Particle.publish()");
      }
      last_publish_ms = millis(); // Limit publish frequency to limit cellular data usage.
    } else {
      last_publish_ms = millis() - 2000; // Don't check if publish required too frequently.
    }

  }
}

void setup() {

  Particle.keepAlive(50);

  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH);

  Serial.begin(115200);
  waitFor(Serial.isConnected, 4000);

  delay(100);

  Serial.printlnf("Device OS v%s", System.version().c_str());
  Serial.printlnf("Free RAM %lu bytes", System.freeMemory());
  Serial.printlnf("Firmware version v%s", firmware_version);

  // Starting Adafruit GPS FeatherWing
  // Note: If the GPS FeatherWing is not attached, the code continues.
  GPS.begin(9600);
  // Turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // Set 1 Hz update rate

  delay(6000);

  randomSeed(millis());
  digitalWrite(D7, LOW);
  Serial.println("Setup complete");
}

void loop() {

  if (PLATFORM_ID == PLATFORM_BORON) {
    CellBattUpdate();
  }

  // Below absolutely required here.
  if (SerialGPS.available()) {
    GPS.read();
    if (GPS.parse(GPS.lastNMEA())) {
      if (GPS.newNMEAreceived()) {
        if (!GPS.parse(GPS.lastNMEA())) {
          // sets the newNMEAreceived() flag to false
        }
      }
    } // GPS
  }

  publishTimer();

}

