## Introduction
This blueprint is a basic asset tracking solution. You will be able to see your moving device on the map from the web and mobile dashboards, monitor it's speed, and receive a notification once the position of your asset has changed. Use it as is or build more functionality on top if you want to receive different data from your moving asset. 

The web and mobile dashboard and datastreams are pre-configured. You will be creating an integration with a Particle Cloud using a detailed step-by-step guide.

## How it Works
We will be using a Particle Boron with attached GPS FeatherWing, that reads the device location. The location data is pushed from the Particle cellular device to Particle Cloud and from there to the Blynk IoT platform via a Particle Webhook and Blynk HTTPs API. The data is then visualized on both a Blynk web dashboard and mobile app. 

**Functional Requirements**   
* Only publish location information when the GPS has a fix and the location has moved more than 122 m / 400 ft since it was powered on
* If the position has changed 122 m / 400 ft, set a flag for that event, make it visible to the user, and allow the user to reset it 
* Track the device location and speed on a map in a web dashboard and mobile app
* Publish the device position after the hardware boots and a GPS fix is obtained
* Publish the date/time in UTC when the device last published data  
* Publish the cellular signal strength, signal quality, and the battery charge status

## Components Used in This Project
- [Particle Console](https://console.particle.io/) to set up the Webhook and activate the Hardware
- Blynk Console and [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) for web and mobile dashboards
- [Particle Web IDE](https://build.particle.io/), [Particle Workbench](https://www.particle.io/workbench/) or [Particle Comand Line](https://docs.particle.io/getting-started/developer-tools/cli/) to upload firmware
- [Particle Boron](https://docs.particle.io/boron/)
- [GPS FeatherWing](https://www.adafruit.com/product/3133)
- USB cable
- [External active 28 dB GPS antenna](https://www.adafruit.com/product/960) (optional, recommended for the best GPS performance)  
- [a SMA to uFL/u.FL/IPX/IPEX RF adapter cable](https://www.adafruit.com/product/851) (optional, recommended for the best GPS performance) 


## 1. Prepare Your Hardware
The Boron is physically stacked on top of the GPS FeatherWing, completing the electrical connection between them. The Boron and the GPS FeatherWing communicate over the Boron UART pins.

![connect-boron-featherwing](https://github.com/blynkkk/blueprints/blob/main/Asset%20Tracker/Images/connect-boron-featherwing.png?raw=true)

## 2. Create a Webhook on Particle Cloud
Create a Particle Webhook to transfer the data from the Particle Cloud to Blynk.
1. Create account or log in into the [Particle Console](https://console.particle.io/)
2. Go to **Products** > **New Product** to create a new Product, and then add your device
3. After the device is added, click on the **Integrations** on the left > **Add New Integration** and select the **Webhook** option
4. Switch to **Custom template** and fill it with the following lines:

```
{
    "name": "",
    "event": "blynk_https_get ",
    "url": "https://ny3.blynk.cloud/external/api/batch/update",
    "requestType": "GET",
    "noDefaults": true,
    "rejectUnauthorized": true,
    "query": 
    {
        "token": "{{t}}",
        "V3": "{{lon}},{{lat}}",
        "V4": "{{spd}}",
        "V5": "{{moved}}",
        "V6": "{{PARTICLE_PUBLISHED_AT}}",
        "V10": "{{v10}}", 
        "V11": "{{v11}}", 
        "V12": "{{v12}}"
     }
} 
```

_The keys on the left (token, V3... V12) refer to Blynk datastreams, and the values on the right reference variables from the firmware that will be passed from the Particle.publish() function. The value ‘PARTICLE_PUBLISHED_AT’ for virtual pin V6 is a Particle pre-defined variable that provides a timestamp for when the webhook is executed._

5. Update **ny3.blynk.cloud** with your server shown in the Blynk.Console lower right. Find the list of valid server addresses [here](https://docs.blynk.io/en/blynk.cloud/troubleshooting)


6. Click on **Create Webhook**

#### The Webhook should look like this:
![particle webhook](https://raw.githubusercontent.com/blynkkk/blueprints/main/Asset%20Tracker/Images/integration-screenshot.png)

## 3. Prepare Required Software
1. Go to [Particle Web IDE](https://build.particle.io/) or install [Particle Workbench](https://www.particle.io/workbench/) or [Particle Comand Line](https://docs.particle.io/getting-started/developer-tools/cli/)
2. Create a new sketch
3. Install the **Adafruit_GPS** Library   

## 4. Prepare the Firmware and Upload It to Your Device
Cellular communication between the hardware and Blynk will utilize the [Blynk HTTPs API](https://docs.blynk.io/en/blynk.cloud/https-api-overview) to minimize cellular data usage. The Particle Boron cellular IoT device will publish a JSON string to the Particle Cloud, referencing a Particle webhook. The webhook reformats the data, and then sends it to the Blynk Cloud via an HTTP GET, updating the Blynk datastreams.  

We need to include TemplateID, Template Name and AuthToken (unique identifier of your device) in the sketch.

1. Click on the **Activate device** action in the Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Follow the proposed steps to prepare and upload the code
3. Restart your Particle Boron and allow it to connect to the Particle Cloud
4. Once the code is successfully uploaded the device dashboard will open automatically

_Check the **Troubleshooting** section at the end of this tutorial if you have issues uploading the firmware_

_Recommendation: to minimize cellular data usage, the minimum publishing interval should be updated to a longer duration such as 300000 ms or 5 min instead of 60000 ms (in the sketch - const uint32_t TIMER_INTERVAL_MS = 60000). Do it after the sketch has been fully tested by changign the number._ 


## 5. Dashboard Breakdown
Widgets are used to display and visualize data, and interact with your device from the web dashboard and mobile app. In order to connect data to a widget, a specific [datastream](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) should be assigned to a widget. You can create datastreams in the widget settings or in the Datastream tab of a Template. Below you can find datastream and widgets used in this project.  

**1. Datastream V3 - GPS Position Coordinates**    
Name: position  
Web widgets: Map (visualise position), Label (coordinates)  
Mobile widgets: Map (visualize position), Labeled Value (coordinates)

**2. Datastream V4 - Device Speed (mph)**   
Name: speed   
Web widgets: Label / Gauge / Chart  
Mobile widgets: Value Display / Labeled Value / Gauge / Chart  
Note: The speed is also added to a web dashboard map widget as an overlay.

**3. Datastream V5 - Position Change Indicator**    
Name: position_changed  
Web widgets: LED / Switch  
Mobile widgets: LED / Switch / Value Display  
Note: V5 will be updated to a value of 1 by the hardware when it has changed by more than 122 m / 400 ft since it was powered on, or since the last time data was published. Position Delta is 122 m / 400 ft can be adjusted in the hardware, but not to smaller number.
Hardware determines the change in position from the last published GPS coordinates. The datastream value is not updated to a value of 0 by the hardware, so this should be done with an [automation](https://docs.blynk.io/en/concepts/automations) if the feature is to be used. 

**4. Datastream V6 - Last Published Position Date and Time**  
Name: last_publish  
Web widgets: Label  
Mobile widgets: Label Display / Value Display   

**5. Datastream V10 - Battery Charge**   
Name: batt_charge  
Web widgets: Label  
Mobile widgets: Label Display / Value Display   
Note: The valie is "no battery" when no battery is connected, otherwise 0.0 to 100.0 where a larger value is better.

**6. Datastream V11 - Cellular Connection Strenght**  
Name: cell_strength  
Web widgets: Label  
Mobile widgets: Label Display / Value Display   
Note: It is -1 when the value is unknown, otherwise it is 0.0 to 100.0 where a larger value is better.

**7. Datastream V12 - Cellular Connection Quality**   
Name: cell_quality  
Web widgets: Label  
Mobile widgets: Label Display / Value Display  
Note: It is -1 when the value is unknown, otherwise 0.0 to 100.0 where a larger value is better.

## 5. Set up Automations  
Let's create an [automation](https://docs.blynk.io/en/concepts/automations) to notify the user when the device position has changed more than 122 m / 400 ft since it was powered on, or since the last time data was published (firmware variable TIMER_INTERVAL_MS).

### First, let's enable the v5 Datastream for Automations:

1. Go to **Automations** tab in the Template
2. Click on the **Edit** button at the top right 
3. Enable both the **Condition** and **Action** switches for the V5 Datastream and click **Save and Apply**.


### 6. How to create the Automation?

1. Go to the **Automations** tab in the Blynk Console or Blynk App and Click **Create Automation**
2. In the Choose Condition dialogue choose the **Device State** option because we want to trigger the automation based on a change in the state of V5
3. Under the **When** section, choose your device, **Position Changed** Datastream, and set the condition to **Has changed**
4. Under the **Do this** section, add the **Send E-Mail** action and enter which message you want to receive, once the position of your asset has changed
5. Press **Save**

Try also to:
* Set up automation to update the value to 0 using the same method</li>
* Try to enable / disable the automation, or edit the automation options from both Web and Mobile

## 7. Testing
1. Open the device **Dashboard** on web and on mobile
2. If your device has connected successfully, a values of cellular connection strengths and quality or battery charge level will be shown
3. The device location and coordinates will not be displayed on the dashboard right away, since it is published when location has changed more than 122 m / 400 ft

## Conclusion
Congratulations on creating a basic asset tracking solution! With this project, you have built a system that allows you to track the movement of your device on a map, both through web and mobile dashboards. You can now monitor its speed and receive notifications whenever the position of your asset changes.  

Try customizing and expanding upon this solution to suit your specific needs. You have the flexibility to receive different types of data from your moving asset, allowing you to adapt the system according to your project requirements.

## Next steps
* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) 
* Learn how to work with [Virtual Pin Datastreams](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) 
* Read more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Configure Blynk to change the state of a built-in LED on a Particle device using this [tutorial](https://docs.blynk.io/en/hardware-guides/particle-part-ii).
* Modify the code for your needs

## Troubleshooting
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the Verify button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible
* Check if the boards connected correctly to each other
* Check that your boards and libraries are up to date
* Go to [Particle Console](https://console.particle.io/) and check that device is **Online** and try to **Ping** it.

## Related Links
Use these detailed tutorials to create a project from scratch that will allow sending data from Particle device to Blynk and controlling a device from Blynk app and web dashboard.
[How to connect a Particle device to Blynk](https://docs.blynk.io/en/hardware-guides/particle)  
[How to control a Particle device with Blynk](https://docs.blynk.io/en/hardware-guides/particle-part-ii)
