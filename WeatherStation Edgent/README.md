# Introduction

This blueprint will help you create a weather station for your home in no time using Blynk Edgent and provisioning! Using a single ESP32 board and two sensors, we will create a full-fledged weather station that monitors four key parameters: temperature, humidity, pressure, and altitude. 

Additionally, we will implement automations to send notifications to your Blynk app when the temperature falls below or exceeds the comfortable range for your home. You will also get notified about excessively high or low humidity levels. This will help you maintain a comfortable microclimate within your home. Sounds great? Let’s get started!

# Components Used in This Project
* Blynk web dashboard and Blynk App for mobile dashboard
* ESP32 Dev Module
* DHT21/AM2301A humidity and temperature sensor
* Barometer BMP280 3.3V


# Prepare your Hardware 

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

3. Don’t forget to connect ESP32 to your computer with a USB cable.

#  Prepare required software

* Install Arduino IDE or PlatformIO
* Install Blynk library for your IDE
* Select the correct board and port in your IDE settings

# Prepare the Firmware and upload it to your device

We need to include TemplateID, AuthToken (unique identifier of your device), and WiFi credentials in the sketch. Follow the steps below.

1. Click on the Activate device action in the Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Download zip arhive 
3. Flash your device
* For Arduino IDE:
 *Open project*->
 *Choose Port and Board*->
 *Press "Upload" button*
* For PlatformIO:
*Open project*->
*Press "PlatformIO: Upload"*
5. Open Blynk app
6. Click "+ New device" and choose "Find devices nearby
7. Click "Start"
8. Connect to "Blynk ... " network
9. Choose network your device will use and click "Continue"
10. Now your device connected! Click "Finish" to open your device. You also will see your device in the Blynk Console.
# Set up Notifications
Let's configure notifications to keep you informed when the temperature or humidity falls outside the comfortable range. This way, you can take action to restore optimal levels as soon as possible.
1. Go to  "Automations" tab 
2. Click "+ Create automations" and choose "Device state"
3. Add a name and choose when you want to receive a notification 
For example, if the temperature is above 28 degrees or below 18, and the humidity is above 60% or below 30%. 
4. In the block "When" choose your device and choose the parameter, that you want to track. You may set "The less than" and "The greater than" and indicate your desired temperature and humidity. 
5. Select if you want to be notified via email or to receive an in-app message on your Blynk app and click "Save"

# Next steps after the device is activated

* Explore the Blynk Web Console and Blynk IoT app, try controlling your device from both
* Explore Blynk Documentation and learn how to work with Virtual Pins
* Improve the code for your needs
* Add more devices


# Troubleshooting

* Make sure you have the latest Blynk Library installed
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the Verify button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* Check that your boards and libraries are up to date









