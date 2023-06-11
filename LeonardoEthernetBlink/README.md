## Introduction

This blueprint is a quick-start tutorial for connecting the Arduino Leonardo board to Blynk using Ethernet. You will be able to control blinking of a built-in LED using a button on the web or mobile dashboard. You can also use this blueprint with similar boards, such as the Arduino Uno and Arduino Mega.

## Components 

* Blynk Console and [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) for web and mobile dashboards
* Arduino IDE or PlatformIO to upload a firmware
* Arduino Leonardo / Uno / Mega board
* Ethernet Shield
* USB cable


## 1. Prepare Your Hardware Before Flashing

1. Connect Ethernet Shield to the Arduino board
2. Connect Arduino board to computer with a USB cable
3. Insert Ethernet cable to Ethernet Shield
It should look like this:
![Hadrware connection](https://raw.githubusercontent.com/blynkkk/blueprints/main/LeonardoEthernetBlink/images/37-4.jpg)

## 2. Prepare Required Software

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/install)
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) for your IDE
3. Install **Ethernet library** for your IDE
4. Select the correct board and port in your IDE settings if you are using Arduino IDE
5. Create a new sketch if you are using Arduino IDE


## 3. Prepare the Firmware and Upload It to Your Device

We need to include TemplateID, AuthToken (unique identifier of your device), and WiFi credentials in the sketch.

1. Click on the **Activate device** action in the Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Follow the proposed steps to prepare and upload the code
3. Once the code is successfully uploaded the device dashboard will open automatically

_Check the Troubleshooting section at the end of this tutorial if you have issues uploading the firmware_

## 4. Testing
1. Open your device **Dashboard** on web and on mobile
2. You should be able to turn an LED on and off using Switch on web and mobile dashboards
3. The LED on a dashboard should indicate the state of the LED on your device  

**If it doesn't work as described**
1. Reboot the device and see if it helps
2. Delete your device and try connecting it again considering the recommendations from the **Troubleshooting** section at the end of this tutorial 

## 5. Dashboard Breakdown 
Widgets are used to display and visualize data, and interact with your device from the web dashboard and mobile app. In order to connect data to a widget, a specific [datastream](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) should be assigned to a widget. You can create datastreams in the widget settings or in the Datastream tab of a Template. Below you can find datastream and widgets used in this project. 

**Datastream V0 - an LED state**  
Name: LED  
Web and mobile widgets: Switch (to control an LED), LED (to show an LED on / off state) 

## Conclusion
Congratulations! You have successfully connected Arduino board to Blynk and now can control a built-in LED from the web dashboard and app. By following this tutorial, you have gained experience working with the Arduino hardware, Arduino IDE, Blynk Console and Blynk App. You can now expand on this project to incorporate sensors or controllers.

## Next Steps

* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [Share Device](https://docs.blynk.io/en/concepts/users) with other users
* Modify the code for your needs
* Add more devices


## Troubleshooting

* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Make sure all other used libraries are up to date
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the Verify button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.

## Related Links
[Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)  
[Documentation](https://docs.blynk.io/en/)
