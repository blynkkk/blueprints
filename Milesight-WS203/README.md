# **Milesight WS302 Sound Level Sensor Blueprint Guide**

This guide explains how to set up the **Milesight WS302 Sound Level Sensor**,
register it with **The Things Network (TTN)**, and integrate it with
**Blynk IoT** for data visualization and control. The guide also provides
steps for interpreting the data presented on the dashboard.

---

## **How to Use This Blueprint**

### **Step 1: Unpacking and Initial Setup**

#### **1.1 Required Components**

- **Milesight WS302 Sound Level Sensor**:\
  The main device used to measure sound levels in dB(A) or dB(C).
- **LoRaWAN Gateway**:\
  Essential for connecting the sensor to the LoRaWAN network and ensuring data is sent to TTN.
- **Antenna**:\
  Ensures reliable wireless communication.
- **Power Supply**:\
  Includes a rechargeable battery for standalone use.
- **Mounting Accessories**:\
  Includes brackets, clamps, and screws to securely attach the sensor to a wall or pole.

#### **1.2 Initial Setup**

1. **Verify Package Contents**:

   - Open the packaging and ensure the following items are included:
     - WS302 Sound Level Sensor
     - Rechargeable battery
     - Antenna
     - Mounting brackets and clamps
     - User manual or quick start guide\
       If anything is missing, contact the supplier immediately.

2. **Charge the Battery (if applicable)**:

   - Before installation, ensure the rechargeable battery is fully charged to maximize performance.
   - Use a compatible charger if the battery needs charging.

3. **Attach the Antenna**:

   - Firmly screw the antenna into the antenna port on the sensor.
   - Ensure the connection is tight but do not overtighten.

4. **Install the Battery**:

   - Open the battery compartment on the sensor.
   - Insert the battery, ensuring correct polarity (+ and -).
   - Close the compartment securely to protect against environmental factors.

5. **Power On the Sensor**:

   - The sensor powers on automatically when the battery is inserted.
   - Observe the LED indicators (if available) to confirm the device is active. Refer to the manual for LED status meanings.

6. **Sensor Placement and Mounting**:

   - **Ideal Placement**:
     - Install the sensor in an open area where it is not obstructed by walls or large objects to ensure accurate sound level readings.
     - Avoid areas prone to vibration or excessive interference.
   - **Mounting the Sensor**:
     - Use the included brackets and clamps to attach the sensor to a wall or pole.
     - Ensure the sensor is mounted securely to prevent movement caused by wind or accidental contact.
     - The sensor should be positioned at a height that minimizes environmental noise distortions, such as reflections from walls.

7. **Environment-Specific Tips**:

   - **Indoor Use**:
     - Place the sensor in a central location away from HVAC systems or machinery to ensure accurate noise measurement.
   - **Outdoor Use**:
     - Ensure the sensor is shielded from rain and direct sunlight using an appropriate cover.

8. **Verify Sensor Alignment**:

   - If the sensor requires directional alignment, use a compass or visual reference to ensure proper orientation.

#### **1.3 Initial Sensor Configuration**

1. **Check Connectivity**:

   - Before proceeding to LoRaWAN configuration, verify that the sensor powers on and communicates via Bluetooth or other local interfaces.

2. **Perform a Test Reading**:

   - Use the **Milesight ToolBox App** or equivalent software to capture a test reading from the sensor. This ensures the sensor is functional before proceeding with network integration.

3. **Update Firmware (if applicable)**:

   - Check the app for any available firmware updates for the sensor.
   - Follow the instructions in the app to install the latest firmware version to ensure optimal performance and compatibility.

4. **Troubleshooting Power-On Issues**:

   - If the sensor does not power on:
     - Recheck battery installation and polarity.
     - Ensure the battery is charged.
     - Inspect for visible damage to the device or connectors.

---

### **Step 2: Configuring the Sensor Using Milesight ToolBox App**

#### **Steps for Configuration**:

1. **Download the Milesight ToolBox App**:

   - Install the app from the [Google Play Store](https://play.google.com) or [Apple App Store](https://apps.apple.com).

2. **Pair the Sensor**:

   - Enable Bluetooth on your smartphone.
   - Open the app and scan for nearby devices.
   - Select the **WS302 Sound Level Sensor** from the list.

3. **Configure LoRaWAN Parameters**:

   - Navigate to **LoRaWAN Settings**.
   - Input the following:
     - **DevEUI**: Found on the sensor label.
     - **AppEUI**: Provided by TTN or in the sensor documentation.
     - **AppKey**: Provided in the sensor documentation.
   - Select the **Frequency Plan** for your region from the following options:

| **Frequency Plan** | **Region**            | **Description**                                                               |
| ------------------ | --------------------- | ----------------------------------------------------------------------------- |
| **EU868**          | Europe                | Operates at 868 MHz. Commonly used across the EU for LoRaWAN deployments.     |
| **US915**          | North America         | Operates at 915 MHz. Used in the United States, Canada, and Mexico.           |
| **AS923**          | Asia-Pacific          | Operates at 923 MHz. Covers countries like Japan, Australia, and New Zealand. |
| **IN865**          | India                 | Operates at 865 MHz. Dedicated plan for deployments in India.                 |
| **AU915**          | Australia/New Zealand | Operates at 915 MHz. Preferred for LoRaWAN in Australia and New Zealand.      |
| **KR920**          | South Korea           | Operates at 920 MHz. Allocated specifically for South Korea.                  |
| **RU864**          | Russia                | Operates at 864 MHz. Used exclusively within Russia.                          |

4. **Adjust Measurement Intervals**:

   - Set the measurement interval to your desired frequency (e.g., every 5 minutes).

5. **Verify Configuration**:

   - Confirm the settings and ensure the sensor is connected to your LoRaWAN gateway.

#### **Alternate Configuration Using NFC**:

1. **Enable NFC on Your Smartphone**:

   - Go to your phone’s settings and ensure NFC is enabled.

2. **Download the Milesight ToolBox App**:

   - Install the app from the [Google Play Store](https://play.google.com) or [Apple App Store](https://apps.apple.com).

3. **Tap to Connect**:

   - Hold your phone close to the NFC tag on the sensor until a prompt appears on your screen.
   - Follow the on-screen instructions to pair the sensor.

4. **Configure LoRaWAN Parameters**:

   - Enter the same details as the Bluetooth configuration:
     - **DevEUI**, **AppEUI**, **AppKey**, and **Frequency Plan**.
   - Save the configuration through the app.

5. **Verify Connection**:

   - Check the app for confirmation that the configuration is successful.

This method is faster and ideal for users who prefer NFC over Bluetooth.

---

### **Step 3: Registering the Sensor on The Things Network (TTN)**

#### **3.1 Create a New Application**

1. **Log in to TTN Console**:

   - Visit the [TTN Console](https://console.cloud.thethings.network/) and log in.

2. **Create an Application**:

   - Navigate to **Applications** > **Add Application**.
   - Enter the following:
     - **Application ID**: A unique name (e.g., `sound-monitor`).
     - **Description**: Optionally, add a description (e.g., `Monitoring environmental noise levels`).
     - **Handler**: Select the handler for your region.
   - Click **Create Application**.

#### **3.2 Add the Sensor as an End Device**

1. **Navigate to the Application**:

   - Open the application you created.

2. **Add an End Device**:

   - Click **Add End Device** and select **Manually**.

3. **Input Device Details**:

   - Enter:
     - **DevEUI**: Found on the sensor label.
     - **AppEUI**: Match the application or documentation.
     - **AppKey**: From the sensor documentation.
   - Choose the frequency plan (e.g., EU868).

4. **Save and Register**:

   - Click **Register End Device**.

#### **3.3 Add a Custom Uplink Payload Formatter**

1. **Navigate to Payload Formatters**:

   - Go to **Payload Formatters** > **Uplink**.

2. **Enter the Formatter Code**:

```javascript
function decodeUplink(input) {
    var data = {};
    data.battery = input.bytes[0]; // Battery level in percentage
    data.la = (input.bytes[1] << 8 | input.bytes[2]) / 10; // Current sound level in dB(A)
    data.laeq = (input.bytes[3] << 8 | input.bytes[4]) / 10; // Equivalent continuous level
    data.lamax = (input.bytes[5] << 8 | input.bytes[6]) / 10; // Maximum sound level
    data.rssi = input.bytes[7]; // Signal strength
    return {
        data: data,
    };
}
```

3. **Save the Formatter**:

   - Click **Save Changes**.

4. **Verify Uplink Data**:

   - Check the **Live Data** tab for decoded data.

---

### **Step 4: Integrating TTN with Blynk**

#### **4.1 Configure MQTT Integration in TTN**

1. **Set Up MQTT Integration**:

   - Go to **Integrations** > **Add Integration**.
   - Select **MQTT**.

2. **Copy Integration Details**:

   - Copy fields:
     - **Server Address**: e.g., `eu1.cloud.thethings.network`.
     - **Port**: Use `1883` or `8883`.
     - **Username**: TTN **AppID**.
     - **Password**: Generate an MQTT API key.

#### **4.2 Configure TTN Integration in Blynk**

1. **Log in to Blynk Console**:

   - Access the [Blynk Console](https://blynk.cloud).

2. **Add TTN Integration**:

   - Go to **Integrations** > **Add Integration**.
   - Fill in:
     - **Integration Name**: WS302-TTN.
     - **Server Address**: TTN MQTT server.
     - **Port**: Use `1883` or `8883`.
     - **Username**: TTN **AppID**.
     - **Password**: MQTT API key.

3. **Map Datastreams**:

   - Assign TTN payload fields (e.g., la, laeq, lamax) to Blynk datastreams.

4. **Save and Activate**:

   - Save the integration.

---

### **Step 5: Monitoring and Controlling the Sensor**

#### **5.1 Web Dashboard Overview**

- **Metrics Displayed**:

  - **Battery**: Remaining battery percentage (e.g., 57%).
  - **LA**: Current sound level in dB(A) (e.g., 41).
  - **LAeq**: Equivalent continuous sound level (e.g., 101).
  - **LAmax**: Maximum sound level (e.g., 85).
  - **RSSI**: Signal strength in dBm (e.g., -110).

- **Custom Chart**:

  - Graphically visualizes sound level trends over time.

- **On/Off Toggle**:

  - Allows remote control of the sensor's operational state.

#### **5.2 Historical Analysis**

- Use Blynk’s graph widgets to view sound trends and analyze historical noise levels.

#### **5.3 Notifications and Alerts**

- Configure Blynk to send alerts when sound levels exceed predefined thresholds.

  **Steps to Automate Alerts in Blynk**:
  1. **Access Automations**:

     - Log in to the Blynk Console and navigate to the "Automations" section.

  2. **Create a New Automation**:

     - Click on "Add New Automation."
     - Define the name (e.g., "Noise Alert") and select the WS302 device.

  3. **Set a Trigger Condition**:

     - Select the parameter (e.g., "LAeq").
     - Set a threshold value (e.g., "> 80 dB").

  4. **Define the Action**:

     - Choose the action type: "Send Notification" or "Trigger Device Action."
     - For notifications, add the message (e.g., "Noise level exceeded 80 dB!").

  5. **Save and Activate**:

     - Save the automation and ensure it is active.
     - Test the automation by generating a sound level above the defined threshold.
  This ensures real-time notifications when sound levels exceed acceptable limits.

#### **5.4 Adding a Location in Blynk**

1. **Navigate to the Location Section**:

   - **Log in to the Blynk Console. On the dashboard, navigate to the "Location" section.**

2. **Add Your Address**:

   - Enter the desired address or coordinates for the sensor's location.
   - Save the location by clicking the "Save" button.

3. **Assign Location in Info & Metadata**:

   - Go to the "Info & Metadata" section of your device settings.
   - In the "Location" field, select the saved location you created earlier.

4. **Confirm and Save**:

   - Save the configuration to ensure the location is updated and linked to your device.

This feature allows users to associate precise geographical information with their devices for better tracking and contextual understanding of the data.


[![Watch the video](https://i.sstatic.net/Vp2cE.png)](https://youtu.be/cuykM1xJTrU?feature=shared)


### **Troubleshooting**

#FIXME: WIP

