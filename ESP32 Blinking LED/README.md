## Introduction
This is a a simple "Hello World" example of Blynk. As a result you will be able to control an LED on the ESP32 DevKit board from web or mobile.

## Components Used in This Project
You would only need the ESP32 Devkit board. No additional hardware is needed. Alternatively, you can wire up your own LED to the ESP32 board.

* Arduino IDE to upload a firmware
* ESP32 DEVKIT board
* USB cable

## 1. Prepare Your Hardware Before Flashing
Connect your device to the computers using USB cable.  

_Your board has to be connected with a **data** USB cable (charging-only cables will not work!)  
Make sure the cable is fully inserted in the port on each end_

## 2. Prepare Required Software
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
3. Select the correct board and port in the **Tools** menu
4. Install the [ESP32 board support](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
5. Create a new sketch  

## 3. Prepare the Firmware and Upload It to Your Device
Now you need to include TemplateID, AuthToken (unique identifier of your device) and WiFi credentials to the sketch

1. Click on the **Activate device** action in Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Follow the proposed steps to prepare and upload the code
3. When code is uploaded, open the Serial Monitor to track connection progress. If all worked correctly, you should see an output similar to this:
```

```
5. When you see that device succesffully connected, go to Blynk.Console to check your device ready to go. 

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


## Conclusion
Congratulations! You have successfully connected ESP32 to Blynk and now can control a built-in LED from the web dashboard and app. By following this tutorial, you have gained experience working with the ESP32, Arduino IDE, Blynk Console and Blynk App. You can now expand on this project to incorporate sensors or controllers. Check out the following section to explore platform functionality further. 

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
