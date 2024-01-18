************************ IN WORK

## Introduction

Header is our new feature for mobile apps. Why do we think you'll love it? It hugely expands design options and makes you app look so complete. See it for yourself - we prepared a Blueprint with a fancy Tesla app assembled from just Blynk's UI components. 

## Components Used in This Project

You can use pretty much any ESP32 dev board. No additional hardware or components are needed.

* [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) and Blynk Console
* Arduino IDE to upload a firmware
* ESP32 DEVKIT board
* Data USB cable (charging-only will not work!)

## 1. Prepare Your Hardware

Connect your device to the computer using a USB cable.

## 2. Prepare Required Software

_This is only needed if you are using Arduino IDE. Skip for PlatformIO._

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
3. Install the [ESP32 board support](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
4. Select the correct board and port in the **Tools** menu

## 3. Prepare the Firmware and Upload It to Your Device

When using Blynk, you need to place TemplateID and DeviceIDin your sketch. We will provide you with the sketch where all of this info is already included. Just follow the next steps:

1. Click on the **Activate device** action in Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Download zip arhive 
3. Upload the sketch to your device: in Arduino IDE go to **Sketch** > **Add File** >
 Select sketch from the zip archive >
 Press **Upload** button
4. Scan a QR code to start the device activation process in the app
5. In the app click **Start**
6. Connect to "Blynk ... " network
7. Select network your device will use and click **Continue**
8. Your device is connected now! Click **Finish** to open your device. You also will see your device in the Blynk Console

_Check the **Troubleshooting** section at the end of this tutorial if you have issues uploading the firmware_  

## 4. Try it out!
1. Try clicking the switch on device dashboard. It should turn the LED on and off
2. Open Blynk app for iOS or Android. You should see the device there. Tap the button to switch the LED on and off

**Not working?**
1. Reboot the device and see if it helps
2. Delete your device and try connecting it again considering the recommendations from the **Troubleshooting** section at the end of this tutorial 

## What's next?

* Here are some ideas on how you can style your app Headers - try to recreate them or come up with your own!
![device-header-design-examples](https://github.com/blynkkk/blueprints/assets/120122081/30f23e0b-aa30-4e30-b77a-20482f8c610e)

* Try to update your firmware [over the air](https://docs.blynk.io/en/blynk.edgent/updating-devices-firmwares-ota)
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [share Device](https://docs.blynk.io/en/concepts/users) with other users
* Learn more about [Blynk.Edgent](https://docs.blynk.io/en/blynk.edgent/overview) and modify your code to utilize WiFi provisioning and over-the-air firmware updates
* Connect more devices using this template

## Troubleshooting

* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Check that all used libraries are up to date
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the **Verify** button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* If you are trying to provision your device the second time or want to connect it to a different WiFi network, you need to reset the hardware configuration. To do so, hold the **Boot** button for 10 seconds.
* Check [Troubleshooting guide](https://docs.blynk.io/en/getting-started/activating-devices/blynk-edgent-wifi-provisioning#troubleshooting) for WiFi provisioning

## Related Links
[Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)  
[Documentation](https://docs.blynk.io/en/)
