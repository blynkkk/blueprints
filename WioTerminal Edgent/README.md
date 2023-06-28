## Introduction

This blueprint will help you create a soil moisture monitoring system using WIO terminal, soil moisture sensor and Blink! We will create a full-fledged soil moisture monitoring system with two key parameters: soil moisture and light.
The blueprint includes Blynk.Edgent solution, which means you will be able to activate the device via your Blynk app just by entering your WiFi credentials (**WiFi provisioning in action**) and perform OTA firmware updates once device has been connected!
Let’s get started!

## Components Used in This Project
* Blynk Console and [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) for web and mobile dashboards
* Arduino IDE or PlatformIO to upload a firmware
* WIO terminal
* Grove - Water - Sensor 
* USB cable


## 1. Prepare Your Hardware 

We need to connect sensor to WIO terminal and then connect the board to the computer with a USB cable to upload the firmware. 

1. Connect Water Sensor to the port on the right side.
2. Connect Seeeduino to PC via a USB cable.


## 2. Prepare Required Software

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/install)  
_If you are using Arduino IDE, follow the next steps (skip for PlatformIO)_
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
3. Install libraries:
   * Blynk librarie
   * https://github.com/jandrassy/ArduinoOTA
   * seeed-studio/Seeed Arduino rpcUnified
   * seeed-studio/Seeed Arduino rpcWiFi
   * SPI
   * ArduinoHttpClient

5. Select the correct board and port in the **Tools** menu
6. Create a new sketch 

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


## 4. Testing
1. Open your device **Dashboard** on web and on mobile
2. You should be able to see the data displayed on the Gauges
3. In a few minutes the historical data should appear on the Charts

**If it doesn't work as described**
1. Reboot the device and check if the data appears on the dashboard
2. Check if both sensors are connected to the board as shown in the **Prepare Your Hardware** section
3. Delete your device and try connecting it again considering the recommendations from the **Troubleshooting** section at the end of this tutorial 

## 6. Dashboard Breakdown
Widgets are used to display and visualize data, and interact with your device from the web dashboard and mobile app. In order to connect data to a widget, a specific [datastream](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) should be assigned to a widget. You can create datastreams in the widget settings or in the Datastream tab of a Template. Below you can find datastreams and widgets used in this project. 

**1. Datastream V0 - Soil moisture**  
Name: Soil moisture   
Web widgets: Gauge (current value), Chart (historical data)  
Mobile widgets: Enhanced Gauge (current value), Chart (historical data)

**2. Datastream V1 - Light**  
Name: Light   
Web widgets: Gauge (current value), Chart (historical data)  
Mobile widgets: Enhanced Gauge (current value), Chart (historical data)  


## Conclusion
Congratulations on creating your own wsoil moisture monitoring system using WIO terminal and Blynk! You can now monitor soil moisture and light. 

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

## Related Links
[Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)  
[Documentation](https://docs.blynk.io/en/)
