## Introduction
This blueprint will help quickly set up bi-directional communication between any Particle hardware and Blynk. You will be able to control an LED from the BLynk mobile app and web dashboard and monitor data sent from the Particle hardware. This project can be easily upgraded to serve a specific use case, like monitoring the fleet ...

### Functional Requirements
- The firmware on the Particle hardware will push data that includes an integer value and a floating point number (simulated sensor value or other source) at a regular interval of every 5 minutes (adjustable in the firmware).
- A date/time stamp in UTC must be included with data sent to Blynk and visible to the user.
- The last integer value, floating point value, and UTC date-time stamp must be displayed on the web dashboard and mobile app.
- The historical values for the integer and floating point value must be displayed in a line chart.  
- Multiple Particle devices must be able to use the same Particle webhook. 
- A button widget on the Blynk web dashboard and mobile app will be configured to send a state change command (1/0 value) back to the Particle hardware that will turn ON/OFF the built-in LED (if no LED on GPIO D7 then the user must configure custom GPIO and connect LED).
- Communication frequency must be configured to minimize data usage by default for the case when a cellular device is employed.  

## How It Works
All communication between the Particle hardware and Blynk will utilize the Blynk HTTP API rather than the [Blynk library](http://library.to/). &nbsp; This minimizes data usage when a Particle cellular device is employed.  

The BLYNK AUTH TOKEN will be sent by the device with each data packet and the Particle webhook will pass this on when it communicates with Blynk via the Blynk HTTP API.  This allows the same Particle integration webhook to be used with multiple Particle devices.  

The firmware sketch sends an integer value from the millis() function (number of milliseconds elapsed since the device started) and a constant floating point value every 5 minutes. &nbsp; The data is pushed from the Particle hardware to a Particle integration webhook. &nbsp; The webhook makes a call to the Blynk HTTP API and updates the Blynk datastreams on the Blynk cloud. &nbsp; The updated datastreams cause the Blynk web dashboard and mobile app widgets configured for those datastreams to be updated.  

The Particle hardware will also be controlled remotely from the Blynk web dashboard or mobile app. When the state of the switch widget on the Blynk web dashboard and mobile app is changed, a Blynk webhook is called. The webhook makes a Particle HTTP API call to a Particle cloud function with a device unique token that sends data to the Particle hardware. A firmware function on the Particle hardware reacts to the data received, returns a result code, and then toggles the virtual LED widget on the Blynk web dashboard and mobile app, and toggles the state of the built-in LED if the Particle hardware has one.

The blueprint includes a sketch (.ino file) that is uploaded to the Particle hardware. The Blynk device template, datastreams, web dashboard ,and mobile app (iOS/Android) are all pre-configured. Instructions are included later in this readme.md on how to configure the Particle integration webhook, generate a Particle access token, and how to create a Blynk webhook. 

## Components Used in This Project
- [Particle Console](https://console.particle.io/) to activate the hardware and set up the integration/webhook. 
- Particle Web IDE, Particle Workbench or Particle Comand Line to upload firmware.
- Any of the following Particle IoT devices:
  - **Tracker One** is complete system including an enclosure. It also comes as a SoM (system on module) known as **Tracker SoM**.  See [Tracker button and LEDs](https://docs.particle.io/hardware/tracker/projects/tracker-buttons-leds/) for details on how to add an LED to the Tracker One. 
  - Any **Boron** cellular devices, including those that are depreciated. &nbsp; All have a built-in LED is on D7.
  - **B Series SoM** system-on-a-module. &nbsp; No built-in LED, must custom install.  
  - **Photon 2** is a WiFi device with built in LED is on D7.
  - **P2** is an SMD module with WiFi and a microcontroller.  No built-in LED.  Replaces the depreciated P1. 
  - **Argon** is a depreciated WiFi device with built in LED is on D7.
  - **Photon** is a depreciated WiFi device with built-in LED on D7.
  - **Electron** is a depreciated cellular device with built-in LED on D7.
  - **E Series** is a cellular device.  No built-in LED.
  - **Core** is a WiFi device with built-in LED on D7. 

## 1. Prepare Your Hardware
1. All Particle devices will require a suitable power connection and either a cellular or WiFi connection. &nbsp; 
2. A virtual LED (Blynk widget) will be used for all hardware to push back data to Blynk and cause the LED widget to turn on or off. Particle devices with a built-in LED connected to GPIO D7 GPIO D7 (Boron, Argon, Photon 2, Photon, Electron, Core) will be detected by the firmware and this physical LED will be turned ON/OFF in addition to the LED widget. 

## 2. Get the Firmware and a Blynk AuthToken
1. If you don't have a Blynk account, then create one. &nbsp; From the Blynk.Console, navigate to 'Templates' -> 'All Blueprints' -> 'Particle Device Blueprint'. &nbsp;
2. After selecting the blueprint, choose the option 'Activate New Device' to generate a Blynk AuthToken and to get the firmware code. &nbsp; The AuthToken generated will be automatically inserted into the firmware. 
3. Upload that firmware to your Particle hardware. &nbsp; This firmware should be used with only one device. &nbsp; You can add more devices by click the 'New Device' button on this page. &nbsp;
4. The Particle device should be breathing cyan if it has the built-in RGB and is connected to the Particle cloud. &nbsp; 

## 3. Create Particle Integration Webhook

A Particle integration webhook running on the Particle cloud will accept the data from the Particle.publish() function executing on the device, and transform it into a HTTPs GET that will post data to the Blynk cloud, updating the corresponding Blynk datastream values. 

1. Create an account or log in to the [Particle Console](https://console.particle.io/)
2. Go to **Products** > **New Product** to create a new Product, and then add your device
3. After the device is added, click on the **Integrations** on the left > **Add New Integration** and select the **Webhook** option
4. Switch to **Custom template** and fill it with the following lines:

```
{
    "name": "blynk_particle",
    "event": "blynk_https_get",
    "url": "https://ny3.blynk.cloud/external/api/batch/update",
    "requestType": "GET",
    "noDefaults": true,
    "rejectUnauthorized": true,
    "query": 
    {
        "token": "{{t}}",
        "V6": "{{PARTICLE_PUBLISHED_AT}}",
        "V14": "{{v14}}", 
        "V15": "{{v15}}", 
        "V16": "{{v16}}",
        "V17": "{{v17}}"
     }
} 
```

_The keys on the left (token, V6, V14, V15, V16, V17) refer to Blynk datastreams (virtual pins), and the values on the right reference variables from the firmware that will be passed from the Particle.publish() function. The value ‘PARTICLE_PUBLISHED_AT’ for virtual pin V6 is a Particle pre-defined variable that provides a timestamp for when the webhook is executed._

5. Update **ny3.blynk.cloud** with your server shown in the Blynk.Console lower right. Find the list of valid server addresses [here](https://docs.blynk.io/en/blynk.cloud/troubleshooting)

6. Click on **Create Webhook**

#### The Webhook should look like this:
![alt text](https://raw.githubusercontent.com/marynablynk/blynk-particle-integration/main/images/particle-webhook.png "Particle webhook")


Particle.publish() call in the firmware:
```
char data[90]; 
// Note the escaped double quotes around the &quot;&quot;t&quot;&quot; for BLYNK_AUTH_TOKEN.  
snprintf(data, sizeof(data), &quot;{\&quot;t\&quot;:\&quot;%s\&quot;,\&quot;v14\&quot;:%u,\&quot;v15\&quot;:%f,\&quot;v16\&quot;:%u,\&quot;v17\&quot;:%u}&quot;, BLYNK_AUTH_TOKEN, millis(), v15, led_state, led_state);
bool pub_result = Particle.publish(&quot;blynk_https_get&quot;, data, PRIVATE);
```

Note that the firmware will pass the unique BLYNK_AUTH_TOKEN defined for each device to the Particle webhook as the variable ‘{{t}}’. This allows each device to call the same webhook, at the expense of increasing the cellular payload for each transmission by 32 bytes.  

You can learn more about Particle webhooks by visiting this [documentation link](https://docs.particle.io/reference/cloud-apis/webhooks/). 

## 4. Generate a Particle Access Token
The Blynk webhook will need a Particle access token in order to make a Particle HTTP API call to the Particle cloud function. &nbsp;

1. Login to your Particle account.
2. Browse to the Particle documentation section ‘[Create a token (browser-based)](https://docs.particle.io/reference/cloud-apis/access-tokens/#create-a-token-browser-based-)’. 
3. Enter your Particle login email and password into the form. &nbsp; If you have MFA (multi-factor authentication) enabled on your account, you will need your MFA code to generate the access token. 
4. Click the ‘Create token’ button to generate a token. &nbsp; Keep this token confidential. 

![alt text](https://github.com/markwkiehl/particle_device_blueprint/raw/fa812deaaa3100b08566136fa750a2a3e0389f4e/particle_device_blueprint%20(10).jpeg "Particle Access Token")

## 5. Create the Blynk Webhook
Control of the Particle hardware remotely from the Blynk web dashboard or mobile app is accomplished using a Blynk webhook and the Particle HTTP API. &nbsp; When the state of the switch widget on the Blynk web dashboard or mobile app is changed, a Blynk webhook assigned to the same datastream is called. &nbsp; The webhook makes a Particle HTTP API call to a Particle cloud function with a device unique token that sends data to the Particle hardware. &nbsp; 

1. In the [Blynk.Console](https://blynk.cloud/), navigate to ‘Settings -> Webhooks’ and create one new webhook for datastream V16 based on the information shown in the next image. &nbsp; 
2. After you are finished configuring the webhook, click the ‘Test webhook’ to verify it doesn’t throw an error (it won’t send the datastream value here, so don’t expect to see the LED on your Particle device change). &nbsp; 
3. Click the ‘Create Webhook’ button to save it and close the dialog. 

Note that the **Blynk webhook request quota is 1 per minute*** so any datastream value changes sooner than 60 seconds will not execute the webhook. &nbsp;

![alt text](https://github.com/markwkiehl/particle_device_blueprint/raw/4551a69255324fa9f0c551440f7514cb6764b464/particle_device_blueprint%20(11).png "Blynk Webhook")

**WEBHOOK URL**

The format is: 
<pre><code>https://api.particle.io/v1/devices/[your 24 character Particle device ID]/blynk_led</code></pre> &nbsp; 

Substitute your Particle [device ID](https://console.particle.io/) and the 40 character access token you generated earlier in the corresponding form fields. &nbsp;  Your 24 character Particle device ID is available in the [Particle console[(https://console.particle.io/). &nbsp; 

The "blynk_led" at the end of the WEBHOOK URL is the Particle cloud function key that is referenced in the firmware as:

<pre><code>
void setup() {
  ...
  Particle.function("blynk_led", blynkLED);
  ...
}
</code></pre>

**HTTP Headers (optional)**

The 'HTTP Headers' with key "Authorization" has a value consisting of the string "Bearer " (with a space after it), and then followed by the 40 character Particle access token. &nbsp;
<pre><code>
Bearer 40_character_Particle_access_token
</code></pre>


## 8. Testing

1. Test the Particle cloud function running in the firmware by calling it from the Particle console. &nbsp;  With your Particle hardware running, visit [here](https://docs.blynk.io/en/hardware-guides/particle-part-ii#firmware) for detailed instructions on how to call 'blynk_led'. &nbsp; Go to your [Particle console](https://console.particle.io/), select the Particle device, and then under the section ‘FUNCTIONS’ on the right side of the screen you will see the function key of ‘blynk_led’ listed. &nbsp; Enter ‘on’ in the ‘Argument’ input area and click the ‘CALL’ button. &nbsp; Observe the Particle device to confirm that the built-in blue LED on D7 turns on. &nbsp; Repeat, this time with the ‘off’ argument to turn off the LED. &nbsp;

![alt text](https://github.com/markwkiehl/particle_device_blueprint/blob/b1bf502a9f0161de09dced117001832adae37930/particle_device_blueprint%20(12).jpg "Particle Function")

2. Verify that your Particle access token is correct by using the Particle API to test it. &nbsp; Detailed instructions on how to do this using [Postman](https://www.postman.com/) can be found [here](https://docs.blynk.io/en/hardware-guides/particle-part-ii#particle-api). &nbsp;

3. Test the Blynk webhook by installing the firmware on your Particle hardware, and then click the ‘Test webhook’ to verify it doesn’t throw an error (it won’t send the datastream value here, so don’t expect to see the LED on your Particle device change). &nbsp;  Then from the Blynk web dashboard or mobile app, toggle the switch assigned to datastream V16 and observe the built-in LED on the hardware if it exists, or the Blynk LED widget if no built-in LED exists. &nbsp;  Wait 60 seconds between each toggle of the switch widget. &nbsp;

4. Review the Particle device log to confirm the device is connected and to see what data has been published from the hardware to the Particle cloud. 

5. Review the Particle integration log to see if it was triggered successfully and the data what was pushed to it from the Particle device. 

## Reference Information

The Blynk blueprint has created a device template with the following datastreams configured:
<table>
  <tr>
    <th>Datastream <br/> Virtual Pin</th>
    <th>Data Type</th>
    <th>Values</th>
    <th>Comment</th>
  </tr>
  <tr>
    <td>V6</td>
    <td>String</td>
    <td>last_publish</td>
    <td>Last UTC date/time data was published from the Particle hardware</td>
  </tr>
  <tr>
    <td>V14</td>
    <td>integer</td>
    <td>millis()</td>
    <td>Simulated sensor data generated by the firmware</td>
  </tr>
  <tr>
    <td>V15</td>
    <td>double</td>
    <td>3.14159</td>
    <td>Simulated sensor data generated by the firmware</td>
  </tr>
  <tr>
    <td>V16</td>
    <td>integer</td>
    <td>0/1</td>
    <td>Controlled by switch widget on Blynk web dashboard and mobile app. &nbsp; Changes in the datastream value will be received by the hardware and then the state of the built-in LED will be changed (if available), and the state of the LED widget on the Blynk web dashboard and mobile app will be updated (V17).</td>
  </tr>
  <tr>
    <td>V17</td>
    <td>integer</td>
    <td>0/1</td>
    <td>LED widget on Blynk web dashboard and mobile app that echos changes received by the hardware for V16. 
	</td>
  </tr>
</table>


Firmware sketch '[particle_device_blueprint.ino](https://github.com/markwkiehl/particle_device_blueprint/blob/487338647eec7ea72928cc17526fe16eb23f1f8b/particle_device_blueprint.ino)' for the Particle device:


<pre><code>
/*
 * Project particle_device_blueprint
 * Description:
 * Author: Mark W Kiehl / Mechatronic Solutions LLC
 * Date: June 2023
 */

#include &quot;Particle.h&quot;

const char* firmware_version = &quot;0.0.0&quot;;

double v15 = 3.14159;
uint8_t led_state = LOW;
bool particle_fn_called = TRUE;	// causes device to publish data immediately after started/boot and connected to Particle cloud.

// Register the Particle cloud function
int blynkLED(String on_or_off);

/////////////////////////////////////////////////////////////////////////
// Blynk

// Update below with your Blynk auth token for your device 
#define BLYNK_AUTH_TOKEN &quot;your Blynk 32 char auth token&quot;

/////////////////////////////////////////////////////////////////////////


bool deviceHasLedOnD7() {
  // Returns TRUE if the device has a built-in LED on D7:
  //  Boron, Argon, Photon 2, Photon, Electron, Core
  // 8: P1
  switch (PLATFORM_ID) {
    case PLATFORM_BORON:
    case PLATFORM_ARGON:
    case 0:  // Core
    case 6:  // Photon  (PLATFORM_PHOTON_PRODUCTION)
    case 10: // Electron  (PLATFORM_ELECTRON_PRODUCTION)
      return TRUE;
    default:
      return FALSE;
  }
} // deviceHasLedOnD7()

/////////////////////////////////////////////////////////////////////////
// Timer

const uint32_t TIMER_INTERVAL_MS = 300000L;
uint32_t timer_last = 0;

void pubToParticleBlynk() {
  if (Particle.connected()) {
    char data[90]; // See serial output for the actual size in bytes and adjust accordingly.
    // Note the escaped double quotes around the &quot;&quot;t&quot;&quot; for BLYNK_AUTH_TOKEN.  
    snprintf(data, sizeof(data), &quot;{\&quot;t\&quot;:\&quot;%s\&quot;,\&quot;v14\&quot;:%u,\&quot;v15\&quot;:%f,\&quot;v16\&quot;:%u,\&quot;v17\&quot;:%u}&quot;, BLYNK_AUTH_TOKEN, millis(), v15, led_state, led_state);
    Serial.printlnf(&quot;Sending to Blynk: '%s' with size of %u bytes&quot;, data, strlen(data));
    bool pub_result = Particle.publish(&quot;blynk_https_get&quot;, data, PRIVATE);
    if (pub_result) {
      timer_last = millis();
    } else {
      Serial.println(&quot;ERROR: Particle.publish()&quot;);
    }
  }
} // pubToParticleBlynk()


void pubTimer() {
  // A timer for publishing data to Particle Cloud, and then continuing to Blynk.
  if (timer_last &gt; millis())  timer_last = millis();
  if ((millis() - timer_last) &gt; TIMER_INTERVAL_MS &amp;&amp; Particle.connected()) {
    pubToParticleBlynk();
    timer_last = millis();
  }
} // pubTimer()


/////////////////////////////////////////////////////////////////////////


void setup() {

  if (deviceHasLedOnD7() == TRUE) {
    pinMode(D7, OUTPUT);
    digitalWrite(D7, LOW);
  }

  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);
  delay(1000);
  Serial.printlnf(&quot;Device OS v%s&quot;, System.version().c_str());
  Serial.printlnf(&quot;Free RAM %lu bytes&quot;, System.freeMemory());
  Serial.printlnf(&quot;Firmware version v%s&quot;, firmware_version);

  // register the Particle cloud function (funcKey, funcName)
  Particle.function(&quot;blynk_led&quot;, blynkLED);

  Serial.println(&quot;Setup complete&quot;);

} // setup()



void loop() {
  
  pubTimer();

  if (particle_fn_called == TRUE) {
    particle_fn_called = FALSE;
    // Publish data to Particle cloud..
    pubToParticleBlynk();
  }
  
  if (deviceHasLedOnD7() == TRUE) {
    digitalWrite(D7, led_state);
  } 

} // loop()


int blynkLED(String on_off) {
  // Custom Particle cloud function that changes the state of the built-in LED
  // on D7 in response to an instruction from Blynk calling this
  // custom cloud function. 
  // Returns the value 1 if the LED has been turned on, and 0 if turned off, 
  // -1 if an unexpected on_off value is received.
  // Cloud functions must return int and take one String argument
  // curl https://api.particle.io/v1/devices/{your 25 char device id}/blynk_led
  // -d access_token={your 40 char access token}
  // -d &quot;args=on/off&quot;
  
  
  if (on_off == &quot;on&quot; || on_off == &quot;1&quot;) {
    particle_fn_called = TRUE;
    led_state = HIGH;
    return 1;
  } else if (on_off == &quot;off&quot; || on_off == &quot;0&quot;) {
    particle_fn_called = TRUE;
    led_state = LOW;
    return 0;
  } else {
    Serial.print(&quot;Unexpected on_off value of: '&quot;); Serial.print(on_off); Serial.println(&quot;'&quot;);
  }
  return -1;

} // blynkLED()
</code></pre>

## Troubleshooting
If your Particle device has a built-in RGB then it should be breathing cyan if it is connected to the Particle cloud.  &nbsp; 

Make sure the BLYNK_AUTH_TOKEN in the sketch 'particle_device_blueprint.ino' matches what is shown in the Blynk console 'Search' -> 'Device' -> 'Device Info'. &nbsp;

Make sure the firmware code provided by activating the Blynk device was uploaded to the hardware. &nbsp;

Perform all of the tests under **Testing** to be sure that each communication step from the Particle hardware to Blynk and back works properly. &nbsp;

## Conclusion
Using this Blynk blueprint accelerates the configuration of a Particle device for bi-directional communication with Blynk. &nbsp; The Blynk blueprint generates the firmware to be installed on the Particle hardware, creates a Blynk device template with datastreams defined, a web dashboard with widgets, and a mobile app with widgets. &nbsp; The developer needs to create a Blynk webhook, a Particle webhook, provision a Blynk device and upload the firmware to the hardware, and acquire a Particle access token. &nbsp;

## Next Steps
The resources generated by this blueprint are easily modified to include more functionality. &nbsp; Blynk provides a NO CODE web dashboard and mobile app for visualizing data from the Particle hardware, and remotely controlling the Particle device.  &nbsp;

The firmware sketch sends an integer and floating point value every 5 minutes to Blynk. &nbsp; The source of the integer and floating point value can be adapted to a particular application by the developer, such as a sensor value. &nbsp; Additional data can be sent from the hardware to Blynk by modifying the firmware, the Particle webhook, and adding datastreams to the Blynk template. &nbsp; 

The data publishing interval default of 5 minutes set in the firmware can be reduced down to every one second. &nbsp; 

## Related Links
[Connect Particle Device to Blynk](https://blynk.io/blog/how-to-connect-a-particle-device-to-blynk)

[How to Control a Particle Device with Blynk](https://blynk.io/blog/how-to-control-particle-device-with-blynk)

[Blynk vs Particle](https://blynk.io/blog/blynk-vs-particle)
