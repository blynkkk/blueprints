## Introduction
This is a a simple "Hello World" example of Blynk. As a result you will be able to control an LED on the ESP32 DevKit board from web or mobile.

## Components Used in This Project
You only need an ESP32 Devkit board. This example was made using ESP-Wroom-32 dev board, but you can use pretty much any ESP32 dev board. No additional hardware or componets are needed. Alternatively, you can wire up your own LED.

* Arduino IDE to upload a firmware
* ESP32 DEVKIT board. 
* USB cable

## 1. Prepare Your Hardware Before Flashing
Connect your device to the computer using a USB cable.  

_Your board has to be connected with a **data** USB cable (charging-only cables will not work!)  
Make sure the cable is fully inserted in the port on each end_

## 2. Prepare Required Software
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
3. Select the correct board and port in the **Tools** menu
4. Install the [ESP32 board support](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
5. Create a new sketch  

## 3. Prepare the Firmware and Upload It to Your Device
When using Blynk, you need to place TemplateID, AuthToken, and WiFi credentials in your sketch. We will provide you with the sketch where all of this info is already included. Just follow the next steps:

1. Click on the **Activate device** action in Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Download zip arhive 
3. Upload the sketch to your device: in Arduino IDE go to **Sketch** > **Add File** >
 Select sketch from the zip archive >
 Press **Upload** button
4. Scan a QR code to start the device activation process in the app
5. In the app click **Start**
6. Connect to "Blynk ... " network
7. Select a WiFi network your device will use and click **Continue**
8. Your device is connected now! Click **Finish** to open your device. You also will see your device in the Blynk Console 

_Check the **Troubleshooting** section at the end of this tutorial if you have issues uploading the firmware_  

## 4. Try it out!
1. Try clicking the switch on device dashboard. It should turn the LED on and off
2. Open Blynk app for iOS or Android. You should see the device there. Tap the button to switch the LED on and off

**Still Not working?**
1. Reboot the device and see if it helps
2. Delete your device and try connecting it again considering the recommendations from the **Troubleshooting** section at the end of this tutorial 

## 5. Project Breakdown 
Every project you make on Blynk becomes a Template which you can use to create and manage similar devices.
Every template consists of: 
- Settings - general settings like which device and connectivity type. For this project it's ESP32 with WiFi
- [Datastreams](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) - channels for time-stamped data transmitted between the device and the cloud. In this project a value of `1` and `0` is transmitted through a Datastream called `LED switch state`.
- Web and mobile dashboards: GUI to send data from web and mobile apps through datastreams to your devices. Dashboards are made of widgets. In this simple project only switch (Web app) and Button (mobile app) are used. They both send `1` or `0` to `LED switch state`  

## Next Steps
* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [share Device](https://docs.blynk.io/en/concepts/users) with other users
* Learn more about [Blynk.Edgent](https://docs.blynk.io/en/blynk.edgent/overview) and modify your code to utilize WiFi provisioning and over-the-air firmware updates
* Modify the code for your needs
* Connect more devices using this template

## Troubleshooting
* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the **Verify** button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* Check [Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues) 

## Related Links
[Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)  
[Documentation](https://docs.blynk.io/en/)
