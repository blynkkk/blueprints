## Introduction
This blueprint is a basic asset tracking solution. You will be able to see your moving device on the map from the web and mobile dashboards, monitor it's speed, and receive a notification once the position of your asset has changed. Use it as is or build more functionality on top if you want to receive different data from your moving asset. 

The web and mobile dashboard and datastreams are pre-configured. You will be creating an integration with a Particle Cloud using detailed step-by-step guide.

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
2. Create account on [Particle Console](https://docs.particle.io/getting-started/console/console/)

## 2. Prepare your Hardware
The Boron is physically stacked on top of the GPS FeatherWing, completing the electrical connection between them. The Boron and the GPS FeatherWing communicate over the Boron UART pins.
![connect-boron-featherwing](https://github.com/blynkkk/blueprints/assets/120122081/05b0c09d-d0e9-41af-afae-d8ebe13ebc61)


## 3. Create a Webhook on Particle Cloud
Create a Particle Webhook to transfer the data from the Particle Cloud to Blynk.
1. Log in into the [Particle Console](https://console.particle.io/)
2. Go to Products > New Product to create a new Product, and then add your device
3. Click on the Integrations > New Integration and select the Webhook option
4. Fill as follows:  
Webhook event name:  <i>blynk_https_get</i>  
Full URL:  <i>https://ny3.blynk.cloud/external/api/batch/update</i>  
_Update "ny3.blynk.cloud" with your server shown in the Blynk.Console lower right. Find the list of valid server addresses [here](https://docs.blynk.io/en/blynk.cloud/troubleshooting)_  
Request type: <i>GET</i>  
5. Open Advanced Settings and switch to Custom Query Parameters  
6. Create the following Query Parameters  

<ul>
"token": "{{t}}", <br />
"V3": "{{lon}},{{lat}}",<br />
"V4": "{{spd}}",<br />
"V5": "{{moved}}",<br>
"V6": "{{PARTICLE_PUBLISHED_AT}}"<br>
</ul>

_The keys on the left (token, V3... V6) refer to Blynk datastreams, and the values on the right reference variables from the firmware that will be passed from the Particle.publish() function. The value ‘PARTICLE_PUBLISHED_AT’ for virtual pin V6 is a Particle pre-defined variable that provides a timestamp for when the webhook is executed._
![alt text](https://github.com/blynkkk/blueprints/blob/0cc36e45a13f865ef768735d6e2e6b03abddcfb1/Asset%20Tracker/Images/integration-info.png)

## 4. Prepare required software
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install the library "Adafruit_GPS"  
3. Select the correct board and port in your IDE settings
4. Create a new sketch

## 5. Prepare the Firmware and upload it to your device
Cellular communication between the hardware and Blynk will utilize the [Blynk HTTPs API](https://docs.blynk.io/en/blynk.cloud/https-api-overview) to minimize cellular data usage. The Particle Boron cellular IoT device will publish a JSON string to the Particle Cloud, referencing a Particle webhook. The webhook reformats the data, and then sends it to the Blynk Cloud via an HTTP GET, updating the Blynk datastreams.  

We need to include TemplateID, AuthToken (unique identifier of your device) in the sketch.

1. Click on the Activate device action in the Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Follow the proposed steps to prepare and upload the code
3. Once the code is successfully uploaded the device dashboard will open automatically
4. Restart your Particle Boron and allow it to connect to the Particle Cloud

_Check the Troubleshooting section at the end of this tutorial if you have issues uploading the firmware_

_Recommendation: to minimize cellular data usage, the minimum publishing interval should be updated to a longer duration such as 300000 ms or 5 min instead of 60000 ms (in the sketch - const uint32_t TIMER_INTERVAL_MS = 60000). Do it after the sketch has been fully tested by changign the number._ 


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
Hardware determines the change in position from the last published GPS coordinates. The datastream value is not updated to a value of 0 by the hardware, so this should be done with an [automation](https://docs.blynk.io/en/concepts/automations) if the feature is to be used.</br>

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
