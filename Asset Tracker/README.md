## Introduction
This blueprint is a basic asset tracking solution. You will be able to see your moving device on the map from the web and mobile dashboards and monitor it's speed. Use it as is or build more functionality on top if you want to receive different data from your moving asset. 

The web and mobile dashboard and datastreams are pre-configured. You will be creating an integration with an Particle Cloud using detailed step-by-step guide.

## How it works
We will be using a Particle Boron with attached GPS FeatherWing, that reads the device location. The location data is pushed from the Particle cellular device to Particle Cloud and from there to the Blynk IoT platform via a Particle Webhook and Blynk HTTPs API. The data is then visualized on both a Blynk web dashboard and mobile app. 

## Hardware
- [Particle Boron](https://docs.particle.io/boron/)
- [GPS FeatherWing](https://www.adafruit.com/product/3133)
- USB cable
- [External active 28 dB GPS antenna](https://www.adafruit.com/product/960) (optional, recommended for the best GPS performance)</br>
- [a SMA to uFL/u.FL/IPX/IPEX RF adapter cable](https://www.adafruit.com/product/851) (optional, recommended for the best GPS performance) 

## 1. Prepare required Software 
1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [Workbench](https://www.particle.io/workbench/)
2. Install [Particle Console](https://docs.particle.io/getting-started/console/console/)

## 2. Prepare your Hardware
The Boron is physically stacked on top of the GPS FeatherWing, completing the electrical connection between them. The Boron and the GPS FeatherWing communicate over the Boron UART pins.

<img src="https://github.com/blynkkk/blueprints/blob/main/Asset%20Tracker/connect-boron-featherwing.png" width=50% height=50%>

## 3. Create a Webhook on Particle Cloud
Create a Particle Webhook to transfer the data from the Particle Cloud to Blynk.
1. Log in into the [Particle Console](https://console.particle.io/)
2. Go to Products > New Product to create a new Product, and then add your device
3. Click on the Integrations > New Integration and select the Webhook option
4. Fill as follows: </br>Webhook event name:  <i>blynk_https_get</i></br> Full URL:  <i>https://ny3.blynk.cloud/external/api/batch/update</i></br>
Update "ny3.blynk.cloud" with your server shown in the Blynk.Console lower right. Find the list of valid server addresses [here](https://docs.blynk.io/en/blynk.cloud/troubleshooting) </br>Request type: <i>GET</i></br>
5. Open Advanced Settings and switch to Custom Query Parameters</br>
6. Create the following Query Parameters</br>
<ul>
"token": "{{t}}", </br>
"V3": "{{lon}},{{lat}}",</br>
"V4": "{{spd}}",</br>
"V5": "{{moved}}",</br>
"V6": "{{PARTICLE_PUBLISHED_AT}}"</br>
</ul>

Note: the keys on the left (token, V3... V6) refer to Blynk datastreams, and the values on the right reference variables from the firmware that will be passed from the Particle.publish() function. The value ‘PARTICLE_PUBLISHED_AT’ for virtual pin V6 is a Particle pre-defined variable that provides a timestamp for when the webhook is executed.

<img src="https://github.com/blynkkk/blueprints/blob/main/Asset%20Tracker/integration-info.png" width=75% height=75%>

## 4. Activate the Blueprint
1. Copy this Blueprints to your Templates by pressing the Use Blueprint button
2. Choose the Activate First Device option - this will generate and show an AuthToken
4. Copy the AuthToken and keep it in a safe place - we will use it in the next section to update "BLYNK_AUTH_TOKEN" within the sketch [blynk_blueprint_asset_tracking.ino](https://raw.githubusercontent.com/markwkiehl/blynk_blueprint_asset_tracking/38192cabe4122f59c3fe6956038b1a33c015e4b6/blynk_blueprint_asset_tracking.ino).

## 5. Prepare the Firmware and upload it to your device
Cellular communication between the hardware and Blynk will utilize the [Blynk HTTPs API](https://docs.blynk.io/en/blynk.cloud/https-api-overview) to minimize cellular data usage. The Particle Boron cellular IoT device will publish a JSON string to the Particle Cloud, referencing a Particle webhook. The webhook reformats the data, and then sends it to the Blynk Cloud via an HTTP GET, updating the Blynk datastreams.  

1. Open the sketch [blynk_blueprint_asset_tracking.ino](https://raw.githubusercontent.com/markwkiehl/blynk_blueprint_asset_tracking/38192cabe4122f59c3fe6956038b1a33c015e4b6/blynk_blueprint_asset_tracking.ino) in [Workbench](https://www.particle.io/workbench/) or other IDE.
2. Install the library "Adafruit_GPS"  
3. In the sketch, find #define BLYNK_AUTH_TOKEN "your_32_char_token" and replace the value in quotes with your AuthToken, obtained in the Activate First Device section of the Blueprint 
4. Save the modified sketch and then upload it to your Particle Boron
5. Restart your Particle Boron and allow it to connect to the Particle Cloud

Recommendation: to minimize cellular data usage, the minimum publishing interval should be updated to a longer duration such as 300000 ms or 5 min instead of 60000 ms (in the sketch - const uint32_t TIMER_INTERVAL_MS = 60000). Do it after the sketch has been fully tested by changign the number. 


## Blynk Web Dashboard Breakdown
Widgets are used to display data from your device on the web and mobile dashboard. To define the data that will be displayed with every widget, a specific Datastream value should be assigned to the widget. </br>

**GPS Position Coordinates** - Datastream V3</br>
Map widget is used to display your asset on the map
Label Display widget is used to show actual longitude and lattitude</br>

**Device Speed (mph)** - Datastream V4</br>
The Label Display widget is used to display this value.</br> 
You also can use any of the following widgets to make it more visual: Value Display / Labeled Value / Gauge / Chart</br>
The speed may also be added to a web dashboard map widget as an [overlay]()(add link to pic). See [example]()(add link to pic).</br>

**Position Change Indicator** - Datastream V5</br>
The LED widget is used to indicate the position change event. You can also us Switch or value Value Display widget.</br>

V5 will be updated to a value of 1 by the hardware when it has changed by more than 122 m / 400 ft since it was powered on, or since the last time data was published. Position Delta is 122 m / 400 ft can be adjusted in the hardware, but not to smaller number.
Hardware determines the change in position from the last published GPS coordinates. The datastream value is not updated to a value of 0 by the hardware, so this should be done with an [automation](https://docs.blynk.io/en/concepts/automations) if the feature is to be used</br>

**Last Published Position Date and Time** - Datastream V6</br>
Label Display is widget used to display when the position was published last time.

## 6. Set up Automations
Let's create an [automation](https://docs.blynk.io/en/concepts/automations) to notify the user when the device position has changed more than 122 m / 400 ft since it was powered on, or since the last time data was published (firmware variable TIMER_INTERVAL_MS). We will be configuring the automation from the Blynk Console.

1. Go to Automations tab in the Blueprint
2. Click on the Edit button at the top right 
3. Enable both the Condition and Action switches for the V5 datastream and click Save and Apply
4. On the Automations page Click Create Automation at the top right of the page
5. In the Choose Condition dialogue choose the Device State option because we want to trigger the automation based on a change in the state of V5
6. Name the automation "position_changed" by editing the field at the top of the page labeled "New Automation" 
7. Under the When section, choose the device "boronb", the datastream "position_cnahged" (V5), and assign the type of datastream value change of "Has changed"
8. Under the Do this section, choose the Send E-Mail option and enter which message you want to receive, once the position of your asset has changed

Try to:
<ul>
  <li> Set up automation to update the value to 0 using the same method</li>
  <li> Find this automation from your Blynk App in the Automations section and try to enable / disable the automation, or edit the automation options</li>
</ul>

## Next steps
* Explore the Blynk [Web Console](blynk.cloud) and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) 
* Learn how to work with [Virtual Pin Datastreams](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) and [Automations](https://docs.blynk.io/en/concepts/automations)
* Modify the code for your needs

## Troubleshooting

## Related Links
[How to connect a Particle device to Blynk](https://docs.blynk.io/en/hardware-guides/particle)<br/>
[How to control a Particle device with Blynk](https://docs.blynk.io/en/hardware-guides/particle-part-ii)<br/>
