## Introduction

This is a example of Blynk.Edgent running on a dual-connectivity board. The LilyGo T-PCIe allows us to use WiFi and Cellular connectivity (with a variety of add-on modems).

In this project, we leverage the Blynk.Edgent solution to demonstrate the ease with which the device can be activated using the Blynk mobile app. Additionally, once the device is connected, you'll be able to perform OTA firmware updates.

Also, the `Terminal` widget is connected to the device console, which enables remote diagnostics and testing of the connectivity.

## Components Used in This Project

* Blynk Console and [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) for web and mobile dashboards
* PlatformIO to upload the firmware
* LilyGo® TTGO T-PCIe base board
* LilyGo® TTGO T-PCIe SIM7000 modem
* Full Band LTE antenna (ships with the modem add-on)
* USB Type C cable
* A suitable Nano SIM card

## 1. Prepare Your Hardware

1. Insert the modem into the PCIe slot on the base board and secure it with 2 screws
2. Connect LTE antenna
3. Insert your SIM card
4. Connect your device to the computer using a USB cable.

_Your board has to be connected with a **data** USB cable (charging-only cables will not work!)  
Make sure the cable is fully inserted in the port on each end_

## 2. Prepare Required Software

This is a **PlatformIO** project. Please install the [**VSCode plugin**][pio_vscode] or [**PlatformIO CLI**][pio_cli].

## 3. Prepare the Firmware and Upload It to Your Device

When using Blynk, you need to place TemplateID in your sketch. We will provide you with the sketch where all of this info is already included. Just follow the next steps:

1. Click on the **Activate device** action in Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Download zip arhive 
3. Flash your device:
*Open project* >
*Press **PlatformIO: Upload***
4. Scan a QR code to start the device activation process in the app
5. In the app click **Start**
6. Connect to "Blynk ... " network
7. Select network your device will use and click **Continue**
   ![Blynk Provisioning](https://raw.githubusercontent.com/blynkkk/blueprints/main/ESP32%20Edgent%20for%20Cellular%20and%20WiFi/Images/provisioning-flow.png)
8. Your device is connected now! Click **Finish** to open your device. You also will see your device in the Blynk Console

_Check the **Troubleshooting** section at the end of this tutorial if you have issues uploading the firmware_  

## 4. Try it out!
1. Open your device **Dashboard** on web and on mobile
2. You should be able to see the data displayed on the Gauges
3. In a few minutes the historical data should appear on the Charts

**Still Not working?**
1. Reboot the device and check if the data appears on the dashboard
2. Delete your device and try connecting it again considering the recommendations from the **Troubleshooting** section at the end of this tutorial 

## 5. Project Breakdown
Every project you make on Blynk becomes a Template which you can use to create and manage similar devices.
Every template consists of: 
- Settings - general settings like which device and connectivity type. For this project it's ESP32 with WiFi
- [Datastreams](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) - channels for time-stamped data transmitted between the device and the cloud. In this project a value of `1` and `0` is transmitted through a Datastream called `LED switch state`.
- Web and mobile dashboards: GUI to send data from web and mobile apps through datastreams to your devices. Dashboards are made of widgets. In this simple project only switch (Web app) and Button (mobile app) are used. They both send `1` or `0` to `LED switch state`  

## Next Steps

* Try to update your firmware [over-the-air](https://docs.blynk.io/en/blynk.edgent/updating-devices-firmwares-ota)
* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [share Device](https://docs.blynk.io/en/concepts/users) with other users
* Learn more about [Blynk.Edgent](https://docs.blynk.io/en/blynk.edgent/overview) and modify your code to utilize WiFi provisioning and over-the-air firmware updates
* Modify the code for your needs
* Connect more devices using this template

## How to Reset a Device Configuration


## Troubleshooting

* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the **Verify** button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* If you are trying to provision your device the second time or want to connect it to a different WiFi network, you need to reset the hardware configuration. To do so, hold the **Boot** button for 10 seconds.
* Check [Troubleshooting guide](https://docs.blynk.io/en/getting-started/activating-devices/blynk-edgent-wifi-provisioning#troubleshooting) for WiFi provisioning

## Related Links
[Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)  
[Documentation](https://docs.blynk.io/en/)


[pio_vscode]: https://docs.platformio.org/en/stable/integration/ide/vscode.html#ide-vscode
[pio_cli]: https://docs.platformio.org/en/stable/core/index.html

