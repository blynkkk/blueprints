# Introduction

This project will help to make your own weather station at home. With one ESP32 board and 2 sensors, we will create a full-fledged weather station with 4 parameters: temperature, humidity, pressure and altitude. There will also be automation here, which will send a notification in the application when the temperature drops below or rises above the comfort level for the home, as well as about too high or too low humidity, which will help to make the microclimate at home comfortable.

# Components Used in This Project
* Blynk web dashboard and Blynk App for mobile dashboard
* ESP32 Dev Module
* DHT21/AM2301A humidity and temperature sensor
* Barometer BMP280 3.3V

# Prepare your Hardware 

For this tutorial, we need the ESP32 Dev Module board, two sensors: DHT21/AM2301A humidity and temperature sensor and
Barometer BMP280 3.3V (atmospheric pressure sensor) and USB cable to connect board to computer.
How to connect ESP32 to DHT21/AM2301A humidity and temperature sensor
![Connecting DHT21](https://raw.githubusercontent.com/YuliiaRudevych/blueprints/main/Weather%20Station/Images/Screenshot%20at%20May%2018%2017-57-29-2.webp)

You have to connect:
1. 5V to 5V in the ESP32
2. GND to GND in the ESP32
3. Data to IO25 in the ESP32

How to connect ESP32 to Barometer BMP280 3.3V (atmospheric pressure sensor)
![Connecting BME](https://raw.githubusercontent.com/YuliiaRudevych/blueprints/main/Weather%20Station/Images/interfacing-bmp280-and-esp32-circuit-diagram.webp)
#  Prepare required software

* Install PlatformIO
* Install Blynk library for PlatformIO and create new sketch:
  1. Open PlatformIO Home > “+ New Project”
  2. Add name, select hardware (I have Esp32 Dev Module), select Arduino framework, click "Finish"
  3. Open "Plathormio.ini" file and paste there this code:
  lib_deps = 
	adafruit/Adafruit BMP280 Library@^2.6.6
	adafruit/DHT sensor library@^1.4.4
	blynkkk/Blynk@^1.2.0

# Prepare the Firmware and upload it to your device

Now you need to include TemplateID, AuthToken (unique identifier of your device) and WiFi credentials to the sketch. Follow next steps to do it.

* Click on the Activate device action in Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
* Enter the Wi-Fi credentials your device will use
* Copy the sketch and paste it to the IDE
* Flash your device :
1. Open the "src" folder and open the "Main.cpp" file
2. Insert the code
3. Press "PlatformIO: Upload"
* The device should open automatically


# Next steps after the device is activated

* Explore the Blynk Web Console and Blynk IoT app, try controlling your device from both
* Explore Blynk Documentation and learn how to work with Virtual Pins
* Improve the code for your needs
* Add more devices


# Also you can create automations :

To do this, you need to open the "automation" tab. Click "+ Create automations" and choose "Device state".
Add name and choose when you want to receive a notification (for example, if the temperature is above 28 degrees or below 18, as well as the humidity is above 60% or below 30%). For this, in the block "When" choose your device and choose parametr, that you want to track. You may set "The less then" and "The greater then" and indicate your desired temperature and humidity. Next step is to choose what to do. You can receve information on the email or in the in-app notification. Choose what wil be comfortable for you and click "Save". This will help you to know when the indicators are too low or too high and correct it.



# Troubleshooting

* Make sure you have the latest Blynk Library installed
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the Verify button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* Check that your boards and libraries are up to date









