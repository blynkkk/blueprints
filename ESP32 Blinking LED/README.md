## Introduction
This project is a quick start tutorial on connecting the ESP32 board to the Blynk IoT. You will be able to control a blinking of an LED through the app and web dashboard. This project is a great introduction to the world of IoT and can be easily expanded to include other sensors and actuators.

The ESP32 is a powerful microcontroller that supports Wi-Fi and Bluetooth connectivity. With the ESP32 and Blynk, you can build a wide range of IoT projects, from home automation to remote monitoring and control of devices.

## Components Used in This Project
In this project we used:
* Blynk web dashboard and [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) for mobile dashboard
* ESP32 DEVKIT board
* USB cable

## 1. Prepare your Hardware before flashing
Connect your device to computers` USB port

_Your board needs to be connected with a data USB cable (charge-only cables will not work).  
Make sure the cable is fully inserted in the port on each end_

## 2. Prepare required software
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
3. Select the correct board and port in Tools menu
4. Install the [ESP32 board support](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
5. Create a new sketch  

## 3. Prepare the Firmware and upload it to your device
Now you need to include TemplateID, AuthToken (unique identifier of your device) and WiFi credentials to the sketch.

1. Click on the **Activate device** action in Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Follow the proposed steps to prepare and upload the code
3. Once the code is successfully uploaded the device dashboard will open automatically



_Check the **Troubleshooting** section at the end of this tutorial if you have issues uploading the firmware_


## Next steps after the device is activated
* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [Share Device](https://docs.blynk.io/en/concepts/users) with other users
* Modify the code for your needs
* Add more devices
## Troubleshooting
* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the **Verify** button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* Check that your boards and libraries are up to date
* Check [Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues) 


## Conclusion
Congratulations! You have successfully connected ESP32 to Blynk and now can control a built-in LED. By following this tutorial, you have gained experience working with the ESP32, Arduino IDE, Blynk Console and Blynk App. You can now expand on this project to incorporate sensors or controllers.

