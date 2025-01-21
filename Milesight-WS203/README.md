# **Milesight WS302 Sound Level Sensor Blueprint Guide**

The **Milesight WS302 Sound Level Sensor** is designed to monitor and analyze
sound levels in various environments, providing metrics such as instantaneous
sound levels (**LA**), equivalent continuous sound levels (**LAeq**), and
maximum sound levels (**LAmax**). It also monitors battery levels and RSSI for
reliable operation. This guide provides step-by-step instructions to set up the
sensor, register it with **The Things Network (TTN)**, and integrate it with
**Blynk IoT** for data visualization and control.

---

## **Step 1: Unpacking and Initial Setup**

### **1.1 Required Components**
- **Milesight WS302 Sound Level Sensor**.
- **LoRaWAN Gateway** for connectivity.
- **Two ER14505 Li-SOCl₂ batteries**.
- **Mounting accessories**: Wall mounting kits or 3M double-sided tape.

### **1.2 Initial Setup**
1. **Verify Package Contents**: Ensure all components are included and undamaged.
2. **Install the Batteries**: Insert the batteries, ensuring correct polarity.
3. **Power On the Sensor**: Hold the power button for 3 seconds. The LED will confirm activation.

---

## **Step 2: Registering the Sensor on The Things Network (TTN)**

### **2.1 Set Up the LoRaWAN Gateway**
1. **Log in to TTN Console**: Visit the [TTN Console](https://console.cloud.thethings.network/).
2. **Add a Gateway**:
   - Navigate to **Gateways** > **Add Gateway**.
   - Enter:
     - **Gateway EUI** (found on the gateway label).
     - **Gateway ID** (e.g., `my-lorawan-gateway`).
     - **Frequency Plan** for your region (see table below).
   - Click **Register Gateway**.
3. **Configure the Gateway**:
   - Follow the manufacturer's instructions to connect the gateway to TTN.
   - Ensure the gateway is online and visible in the TTN Console.
   - *[Insert Screenshot of TTN Gateway Registration Page]*

#### **Frequency Plans**
| **Frequency Plan** | **Region**            | **Description**                                                                 |
|--------------------|-----------------------|---------------------------------------------------------------------------------|
| **EU868**         | Europe                | Operates at 868 MHz. Commonly used across the EU for LoRaWAN deployments.      |
| **US915**         | North America         | Operates at 915 MHz. Used in the United States, Canada, and Mexico.            |
| **AS923**         | Asia-Pacific          | Operates at 923 MHz. Covers countries like Japan, Australia, and New Zealand. |
| **IN865**         | India                 | Operates at 865 MHz. Dedicated plan for deployments in India.                  |
| **AU915**         | Australia/New Zealand | Operates at 915 MHz. Preferred for LoRaWAN in Australia and New Zealand.       |
| **KR920**         | South Korea           | Operates at 920 MHz. Allocated specifically for South Korea.                   |
| **RU864**         | Russia                | Operates at 864 MHz. Used exclusively within Russia.                           |

---

### **2.2 Create a New Application**
1. **Log in to TTN Console**.
2. **Create an Application**:
   - Navigate to **Applications** > **Add Application**.
   - Enter:
     - **Application ID**: A unique name (e.g., `sound-monitor`).
     - **Description**: (e.g., `Monitoring environmental noise levels`).
     - **Handler**: Select the handler for your region.
   - Click **Create Application**.
   - *[Insert Screenshot of TTN Application Creation Page]*

> **Note:** A TTN application can support only one type of sensor. Ensure that
> all devices in this application are of the same type (e.g., WS302). If you
> need to use more than one type of sensor, please create a new application for
> each sensor type.
---

###FIXME: add downlink payload formater

### **2.3 Add a Custom Uplink and Downlink Payload Formatter**
To ensure data is properly decoded:
1. **Navigate to Payload Formatters** in TTN.
2. Paste this JavaScript code:
   ```javascript
   function decodeUplink(input) {
       return {
           data: {
               LA: input.bytes[0],       // Instantaneous sound level
               LAeq: input.bytes[1],    // Equivalent continuous sound level
               LAmax: input.bytes[2],   // Maximum sound level
               battery: input.bytes[3]  // Battery level
           }
       };
   }
   ```
3. **Save Changes**.
   - *[Insert Screenshot of Payload Formatter in TTN Console]*

---

### **2.4 Pair the Sensor with TTN Application**
1. **Open Milesight ToolBox App**:
   - Pair the sensor via NFC.
   - Navigate to **LoRaWAN Settings**.
   - *[Insert Screenshot of LoRaWAN Settings in ToolBox App]*
2. **Configure LoRaWAN Parameters**:
   - **DevEUI**: Use default value (found on the sensor label).
   - **AppEUI**: Use default value from manufacturer or generate a new one.
   - **AppKey**: Use default from the manufacturer or generate a new one.
   - **Frequency Plan**: Match the frequency plan configured in TTN.
   - **RX2 Data Rate**: Set to DR3 (SF9, 125 kHz).
   - **Spreading Factor**: Set to SF10-DR2.
   - **Default Application Port**: Set to 85.
   - Save the settings.
---

### **2.5 Configure MQTT Integration**
1. **Navigate to TTN Integration Settings**:
   - In the TTN Console, go to your application and select **Integrations** > **Add Integration**.
2. **Select MQTT**:
   - Click **MQTT** from the list of available integrations.
3. **Configure MQTT Details**:
   - **Server Address**: Enter the TTN server address (e.g., `eu1.cloud.thethings.network` for Europe).
   - **Port**: Use `1883` (unsecured) or `8883` (secured).
   - **Username**: Enter your TTN **Application ID**.
   - **Password**: Generate an **MQTT API Key** from the TTN Console and use it here.
   - *[Insert Screenshot of TTN MQTT Configuration Screen]*
4. **Save and Test**:
   - Save the integration settings and verify that TTN can send uplink messages via MQTT.
   - *[Insert Screenshot of Successful MQTT Integration]*

---

## **Step 3: Integrating TTN with Blynk**

### **3.1 Configuring Blynk Integration via MQTT**
1. **Set Up MQTT in Blynk**:
   - Navigate to **Developer Zone** > **Integrations** > **The Things Stack**.
   - Enter:
     - **Hostname**: MQTT server address (e.g., `eu1.cloud.thethings.network`).
     - **Port**: `1883` or `8883`.
     - **Username**: TTN Application ID.
     - **Password**: MQTT API key.
   - Click **Connect**.

2. **Test Integration**:
   - Verify the status changes to **Connected** in Blynk.
   - Confirm data appears in the **Devices** section.
   - *[Insert Screenshot of Successful Integration]*
---

### **3.2 Onboarding Using Static Tokens**
1. **Prepare a CSV File**:
   Create a CSV file with the following format to list the device credentials:
   ```csv
   Device EUI,Join EUI,Application Key
   0018B20000000101,70B3D57ED0000010,2B7E151628AED2A6ABF7158809CF4F3C
   0018B20000000102,70B3D57ED0000011,3B7E151628AED2A6ABF7158809CF4F3D
   0018B20000000103,70B3D57ED0000012,4B7E151628AED2A6ABF7158809CF4F3E
   ```
   - *[Insert Screenshot of Example CSV File]*

2. **Upload the CSV File**:
   - In Blynk, go to **Developer Zone** > **Static Tokens**.
   - Click **Generate Static Tokens** > **Create From File**.
   - Upload the CSV file.
   - Blynk will generate unique QR codes for each device.
   - *[Insert Screenshot of Static Token Generation Screen]*

3. **Scan the QR Codes**:
   - Use the Blynk mobile app or web dashboard to scan the QR codes.
   - Once scanned, the devices will be automatically created in Blynk and registered with The Things Stack.

  ---

## **Step 4: Monitoring and Analyzing Data**

### **4.1 Dashboard Overview**
The dashboard is preconfigured and provides an intuitive interface for monitoring sensor data in real-time. Key features include:

- **Device Overview:**
  - Displays the **Device Name**, **Device Owner**, and **Company Name**.
  - Shows the device's **online/offline status**.
- **Metrics (Virtual Pins):**
  - **Battery (V0):** Displays the battery percentage.
  - **LA (V1):** Instantaneous sound level.
  - **LAeq (V2):** Continuous noise exposure.
  - **LAmax (V3):** Maximum recorded sound level.
  - **RSSI (V6):** Signal strength.
- **Custom Chart:**
  - Provides a time-series visualization of metrics like **LA**, **LAeq**, and **LAmax**.
  - Selectable time intervals (e.g., 1 hour, 6 hours, 1 day).
- **Location Map:**
  - Displays the sensor's geographical location.

---

### **4.2 Setting Alerts**
1. **Log in to Blynk Console**.
2. **Create Automations**:
   - Set triggers for specific thresholds (e.g., `LAeq > 80 dB`).
   - Define actions (e.g., send notifications).
3. **Save and Test**:
   - Simulate events to ensure triggers activate correctly.

---

## **Step 5: Adding Location in Blynk**

### **5.1 Configuring Location**
1. **Go to Location Section in Blynk**:
   - In the Blynk dashboard, navigate to the **Location** section.
2. **Add the Address**:
   - Enter the sensor's address or drag the pin on the map to the correct location.
   - Save the location.
   - *[Insert Screenshot of Location Configuration in Blynk]*
3. **Assign Location in Metadata**:
   - Navigate to **Info & Metadata** in Blynk.
   - Assign the saved location to the device.

---

## **Error Handling and Troubleshooting**

### **6.1 Common Issues**
1. **Sensor Issues**:
   - Check battery polarity and charge.
   - Reset the sensor if unresponsive.
2. **Connectivity Problems**:
   - Verify LoRaWAN settings and gateway connection.
   - Test MQTT integration.
3. **Data Issues**:
   - Check the payload formatter in TTN.
   - Debug MQTT connections with tools like MQTT Explorer.

This comprehensive guide ensures seamless integration of the Milesight WS302 Sound Level Sensor with TTN and Blynk for robust environmental noise monitoring.


### FIXME: fix the video url
[![Watch the video](https://i.sstatic.net/Vp2cE.png)](https://youtu.be/cuykM1xJTrU?feature=shared)


