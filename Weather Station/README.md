## Introduction

This blueprint will help you create a weather station for your home in no time! Using a single ESP32 board and two sensors, we will create a full-fledged weather station that monitors four key parameters: temperature, humidity, pressure, and altitude. 

Additionally, we will implement automations to send notifications to your Blynk app when the temperature falls below or exceeds the comfortable range for your home. You will also get notified about excessively high or low humidity levels. This will help you maintain a comfortable microclimate within your home. Sounds great? Let’s get started!

## Components Used in This Project
* Blynk Console and [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) for web and mobile dashboards
* Arduino IDE or PlatformIO to upload firmware
* ESP32 Dev Module
* DHT21/AM2301A humidity and temperature sensor
* Barometer BMP280 3.3V
* USB cable


## 1. Prepare Your Hardware 

We need to connect both sensors to ESP32 Dev Module and then connect the board to the computer with a USB cable to upload the firmware. 

1. Connect DHT21/AM2301A sensor to ESP32:

* 5V to 5V on the ESP32
* GND to GND on the ESP32
* Data to IO25 on the ESP32

![Connecting DHT21](https://raw.githubusercontent.com/YuliiaRudevych/blueprints/main/Weather%20Station/Images/Screenshot%20at%20May%2018%2017-57-29-2.webp)

2. Connect Barometer BMP280 3.3V to ESP32:
* VCC to 3Y3 on the ESP32
* GND to GND on the ESP32
* SDA to D21 on the ESP32
* SCL to D22 on the ESP32

![Connecting BME](https://raw.githubusercontent.com/YuliiaRudevych/blueprints/main/Weather%20Station/Images/interfacing-bmp280-and-esp32-circuit-diagram.webp)

3. Don’t forget to connect ESP32 to your computer with a USB cable


## 2. Prepare Required Software

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/install)
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) for your IDE
3. Install **Adafruit BMP280 Library** and **DHT sensor Library** if you are using Arduino IDE (in Platformio they will be installed automatically)
4. Select the correct board and port in your IDE settings
5. Create a new sketch if you are using Arduino IDE


## 3. Prepare the Firmware and Upload it To Your Device
We need to include TemplateID, AuthToken (unique identifier of your device), and WiFi credentials in the sketch.

1. Click on the Activate device action in the Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Follow the proposed steps to prepare and upload the code
3. Once the code is successfully uploaded the device dashboard will open automatically  

_Check the Troubleshooting section at the end of this tutorial if you have issues uploading the firmware_


## 4. Set up Notifications
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
3. In a few minutes the historical data should be displayed on the Charts

**If it doesn't work as described**
1. Reboot the device and check if data appeared on the dashboard
2. Check if both sensors connected to the board as it shown in the **Prepare Your Hardware** section
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

Check out the following section to explore functionality of the platform and try modifying your project.

## Next Steps

* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [Share Device](https://docs.blynk.io/en/concepts/users) with other users
* Modify the code for your needs
* Add more devices


## Troubleshooting

* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the Verify button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* Check that your boards and libraries are up to date
