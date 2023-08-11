## Introduction

This blueprint will help you create a weather station for your home in no time! Using a single ESP32 board and two sensors, we will create a full-fledged weather station that monitors four key parameters: temperature, humidity, pressure, and altitude.

The blueprint includes Blynk.Edgent solution, which means you will be able to activate the device via your Blynk app just by entering your WiFi credentials (**WiFi provisioning in action**) and perform OTA firmware updates once device has been connected!

Additionally, we will implement automations to send notifications to your Blynk app when the temperature falls below or exceeds the comfortable range for your home. You will also get notified about excessively high or low humidity levels. This will help you maintain a comfortable microclimate within your home. Sounds great? Let’s get started!

## Components Used in This Project
* Blynk Console and [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) for web and mobile dashboards
* Arduino IDE or PlatformIO to upload a firmware
* ESP32 Dev Module
* DHT21/AM2301A humidity and temperature sensor
* Barometer BMP280 3.3V
* USB cable


## 1. Prepare Your Hardware 

We need to connect both sensors to ESP32 Dev Module and then connect the board to the computer with a USB cable to upload the firmware. 

1. Connect DHT21/AM2301A sensor to ESP32:

* 5V to 5V on the ESP32
* GND to GND on the ESP32
* Data to GPIO25 on the ESP32

![Connecting DHT21](https://raw.githubusercontent.com/blynkkk/blueprints/main/ESP32%20Weather%20Station/Images/Screenshot%20at%20May%2018%2017-57-29-2.webp)

2. Connect Barometer BMP280 3.3V to ESP32:
* VCC to 3V3 on the ESP32
* GND to GND on the ESP32
* SCL to GPIO18 on the ESP32
* SDA to GPIO23 on the ESP32
* CSB to GPIO5 on the ESP32
* SDO to GPIO19 on the ESP32


3. Don’t forget to connect ESP32 to your computer with a USB cable.

## 2. Prepare Required Software

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/install)  
_If you are using Arduino IDE, follow the next steps (skip for PlatformIO)_
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
3. Install **Adafruit BMP280 Library** and **DHT sensor Library** 
4. Select the correct board and port in the **Tools** menu
5. Create a new sketch 

## 3. Prepare the Firmware and Upload It to Your Device

We need to include TemplateID and Template Name. Follow the steps below.

1. Click on the Activate device action in the Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Download zip arhive 
3. Flash your device
* For Arduino IDE:
 *Go to **Sketch*** > ***Add File*** >
 *Select sketch from the zip archive* >
 *Press **Upload** button*
* For PlatformIO:
*Open project* >
*Press **PlatformIO: Upload***
4. Scan a QR code to start the device activation process in the app
5. Click **Start**
6. Connect to "Blynk ... " network
7. Select network your device will use and click **Continue**
8. Your device is connected now! Click **Finish** to open your device. You also will see your device in the Blynk Console

## 4. Set Up Notifications
Let's configure notifications to keep you informed when the temperature or humidity falls outside the comfortable range. This way, you can take action to restore optimal levels as soon as possible.
1. Go to the **Automations** tab 
2. Click **+Create automation** and choose **Device state**
3. Add a name and choose when you want to receive a notification 
For example, if the temperature is above 28 degrees or below 18, and the humidity is above 60% or below 30%. 
4. In the block **When** choose your device and choose the parameter, that you want to track. You may set "The less than" and "The greater than" and indicate your desired temperature and humidity. 
5. Select if you want to be notified via email or to receive an in-app message on your Blynk app and click Save

## 5. Testing
1. Open your device **Dashboard** on web and on mobile
2. You should be able to see the data displayed on the Gauges
3. In a few minutes the historical data should appear on the Charts

**If it doesn't work as described**
1. Reboot the device and check if the data appears on the dashboard
2. Check if both sensors are connected to the board as shown in the **Prepare Your Hardware** section
3. Delete your device and try connecting it again considering the recommendations from the **Troubleshooting** section at the end of this tutorial 

## 6. Dashboard Breakdown
Widgets are used to display and visualize data, and interact with your device from the web dashboard and mobile app. In order to connect data to a widget, a specific [datastream](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) should be assigned to a widget. You can create datastreams in the widget settings or in the Datastream tab of a Template. Below you can find datastreams and widgets used in this project. 

**1. Datastream V0 - Temperature**  
Name: temperature   
Web widgets: Gauge (current value), Chart (historical data)  
Mobile widgets: Enhanced Gauge (current value), Chart (historical data)

**2. Datastream V1 - Humidity**  
Name: humidity   
Web widgets: Gauge (current value), Chart (historical data)  
Mobile widgets: Level (current value), Chart (historical data)  

**3. Datastream V3 - Altitude**  
Name: altitude   
Web widgets: Gauge (current value), Chart (historical data)  
Mobile widgets: Level (current value), Chart (historical data)  

**4. Datastream V4 - Pressure**  
Name: pressure   
Web widgets: Gauge (current value), Chart (historical data)  
Mobile widgets: Level (current value), Chart (historical data) 

## Conclusion
Congratulations on creating your own weather station using ESP32 and Blynk! You can now monitor temperature, humidity, pressure, and altitude. Plus, you'll receive notifications on your Blynk app for temperature and humidity thresholds. Enjoy your new weather station and its benefits for a comfortable home!

Check out the following section to explore functionality of the platform and try modifying your project further.

## Next Steps

* Try to update your firmware [over-the-air](https://docs.blynk.io/en/blynk.edgent/updating-devices-firmwares-ota)
* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [Share Device](https://docs.blynk.io/en/concepts/users) with other users
* Modify the code for your needs
* Add more devices


## Troubleshooting

* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Check that all used libraries are up to date
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the Verify button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* If you are trying to connect the same device after it was connected once, you may need to factory reset the device. 

#### How to Reset a Device Configuration  
If your mobile device does not detect the Blynk network, then you most likely need to reset the configuration of your ESP32. Follow the steps below.
   - Open the serial port terminal.
   - Press and hold the **Boot** button on your ESP32 for 10 seconds. The serial port monitor terminal should display the following message:
        - [XXXXX] Hold the button for 10 seconds to reset the configuration…
   - After 10 seconds, release the **Boot** button. You should see the following in the terminal:
        - [XXXXX] RUNNING => RESET_CONFIG
        - [XXXXX] Resetting configuration!
        - [XXXXX] Configuration stored to flash
        - [XXXXX] RESET_CONFIG => WAIT_CONFIG
        - [XXXXX] Scanning networks..
   - Search the Blynk network again with your mobile device using the QR code.

## Related Links
[Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)  
[Documentation](https://docs.blynk.io/en/)
