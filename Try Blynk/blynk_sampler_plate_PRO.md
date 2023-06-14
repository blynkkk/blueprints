# Discover Blynk: A Taste of Innovation

## 1. What's on the Menu?

This guide will introduce you to the variety of Blynk features, taking you on a tour through some of the most popular functionalities. Here's what's on the menu today:

- Learn to activate a new device by connecting iy to your home or office WiFi through Blynk.app 
- Discover the correct way to transmit data from your device to Blynk.app (Hint: It involves built-in timers)
- Learn how to receive and process data from the app on your device
- Create an alert and see it as a notification in the app 
- Explore some cool app widgets and learn what you can do with UI

## 2. Before We Dive In... 

Ensure you are equipped with the following:

- ESP32 Module: This guide is verified with the ESP32 Wroom model **AMAZON_LINK**, but it's compatible with most ESP32 development boards available in the market.
- Blynk App: Installed on your smartphone (Available on [iOS](https://apps.apple.com/app/blynk/id808760481) and [Android](https://play.google.com/store/apps/details?id=cc.blynk)).
- Arduino IDE: Installed on your computer. Feel free to use Platformio or other IDEs.
- Basic understanding of programming ESP32 using the Arduino framework, along with knowledge on flashing sketches to your device.

## 3. Hardware Setup

This blueprint doesn't require any additional equipment except for ESP32 development board. All you need is to have your IDE open and your ESP32 connected with the USB cable.

## 4. Software Setup

### Arduino IDE

**COMMENT:** This process is an essential part of each blueprint, or it should be integrated into the BPs UI at a platform level.

1. Install the ESP32 board package:
    - Launch the Arduino IDE.
    - Navigate to File -> Preferences. **screenshot**
    - In the "Additional Boards Manager URLs" field, insert this URL: `https://dl.espressif.com/dl/package_esp32_index.json` **screenshot or GIF**
    - Proceed to Tools -> Board -> Boards Manager. **screenshot or GIF**
    - Search for ESP32 and install it.
2. Connect your ESP32 board using a USB cable.
3. Verify that the Arduino IDE recognizes your board. **screenshot**
4. Install the Blynk Library. If it's already installed, ensure it's updated to the latest version. **screenshot or GIF**



### Platformio
TODO


<br>

# WIP BELOW:

Widgets: 
styled button
switch = turn on LED
slider = notification threshold or data interval (stroboscope example)
lottie for LED or smth
spacer
Labels
Formatted text
Segmented switch (multiplier for chart data?)or random, sine, saw shapes (change text desription based on selected choice = set properties, + change image
Simple or superchart
page(s)
Image gallery
Gauge with gradient

Use device welcome page for some onboarding? 

Hide widgets with button? Disable  



  
## 5. Programming 

### 5.1 Installing Blynk Library

- In Arduino IDE, go to Sketch -> Include Library -> Manage Libraries.
- Search for Blynk and install it.

### 5.2 Setting Up the Blynk App

- Open the Blynk app on your smartphone.
- Create a new project and select ESP32 as your hardware model.
- You will receive an auth token via email. Make sure to save it.

### 5.3 Writing the Code

Here's a basic example of how to send and receive data using Blynk. Don't forget to replace `<YourAuthToken>` with your auth token.

```cpp
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Replace with your network credentials
const char* ssid = "<YourNetworkSSID>";
const char* password = "<YourNetworkPassword>";

// Replace with your unique Blynk token
char auth[] = "<YourAuthToken>";

void setup() {
  // Begin Blynk
  Blynk.begin(auth, ssid, password);
}

void loop() {
  // Run Blynk
  Blynk.run();
}

// Send data to Blynk (virtual pin V1)
BLYNK_READ(V1) {
  int sensorData = analogRead(34); // Assuming sensor data is read from pin 34
  Blynk.virtualWrite(V1, sensorData);
}

// Receive data from Blynk (virtual pin V2)
BLYNK_WRITE(V2) {
  int receivedData = param.asInt(); // Get value as integer
  // Do something with received data
}

// Send notifications
void sendNotification() {
  Blynk.notify("Notification: Alert triggered!"); // Replace with your message
}
```

## 6. Testing

Upload the code to your ESP32 module using the Arduino IDE. Open the Blynk app and check if you're receiving data on virtual pin V1. Try sending data from the app to virtual pin V2 and verify if it's correctly received by the module.

## 7. Dashboard Setup

In the Blynk app, create widgets for virtual pins V1 and V2. You can choose a gauge or graph for V1 to display sensor data, and a button or slider for V2 to send data.

## 8. Conclusion

Congratulations! You've successfully set up your ESP32 module with Blynk. You can now send
