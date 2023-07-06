## Introduction

This blueprint will help you create a soil moisture and light monitoring system for your beloved plants! We will use a Seeed WIO terminal, soil moisture sensor, and Blynk!   

The blueprint includes Blynk.Edgent solution, which means you will be able to activate the device via your Blynk app just by entering your WiFi credentials (**WiFi provisioning** in action) and perform OTA firmware updates once the device has been connected! Let’s get started!

## Components Used in This Project
* [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/install) to upload a firmware
* [Seeed WIO Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html?queryID=cf4357665409124c32d669c13a54e006&objectID=4509&indexName=bazaar_retailer_products)
* [Seeed Grove Water Sensor](https://www.seeedstudio.com/Grove-Water-Sensor.html) 
* USB cable


## 1. Prepare Your Hardware 

We need to connect a sensor to the WIO Terminal and then connect the board to the computer with a USB cable to upload the firmware. 

1. Connect Water Sensor to the port on the right side.
2. Connect Seeeduino to PC via a USB cable.


## 2. Prepare Required Software

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/install)  
_If you are using Arduino IDE, follow the next steps (skip for PlatformIO)_
2. Install the following libraries:
   * [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
   * https://github.com/jandrassy/ArduinoOTA
   * seeed-studio/Seeed Arduino rpcUnified
   * seeed-studio/Seeed Arduino rpcWiFi
   * SPI
   * ArduinoHttpClient
3. Select the correct board and port in the **Tools** menu
4. Create a new sketch 

## 3. Prepare the Firmware and Upload It to Your Device

When using Blynk, you need to place TemplateID, TemplateName, AuthToken, and WiFi credentials in your sketch. We will provide you with the sketch with the two first already included, and the latter two will be included automatically during device activation - this scenario is possible because we are using [Blynk.Edgent](https://docs.blynk.io/en/blynk.edgent/overview) in this project. Follow the steps below.  

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
6. Connect to the "Blynk ... " network
7. Select the network your device will use and click **Continue**
8. Your device is connected now! Click **Finish** to open your device. You also will see your device in the Blynk Console
  
_Check the **Troubleshooting** section at the end of this tutorial if you have issues uploading the firmware_  

## 4. Try It Out!
1. You should be able to see real time data displayed on mobile and web dashboard Gauges
2. In a few minutes the historical data should appear on the Chart

**Not working?**
1. Reboot the device and check if the data appears on the dashboard
2. Check if both sensors are connected to the board as shown in the **Prepare Your Hardware** section
3. Delete your device and try connecting it again considering the recommendations from the **Troubleshooting** section at the end of this tutorial 

## 6. Template Breakdown
Every project you make on Blynk becomes a Template that you can use to create and manage similar devices.
Every template consists of: 
- Settings - general settings like which device and connectivity type. For this project, it's Seeed Wio Terminal with WiFi
- [Datastreams](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) - channels for time-stamped data transmitted between the device and the cloud. In this project, sensor data transmitted through Datastreams called `Moisture` and `Light`.
- Web and mobile dashboards - GUI to send data from web and mobile apps through datastreams to your devices. Dashboards are made of widgets. In this project, we used two Gauges (Enhanced Gauge on Mobile) to display real time data and Chart widgets for historical data.  

## Conclusion
Congratulations on creating your own soil moisture and light monitoring system using the WIO Terminal and Blynk! 

Check out the following section to explore the platform functionality and try modifying your project further.

## Next Steps

* Try to update your firmware [over-the-air](https://docs.blynk.io/en/blynk.edgent/updating-devices-firmwares-ota)
* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [Share Device](https://docs.blynk.io/en/concepts/users) with other users
* Add more sensors and modify the firmware to level up you plant monitoring project
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
