# **Milesight WS302 Sound Level Sensor Blueprint Guide**

The **Milesight WS302 Sound Level Sensor** is designed to monitor and analyze
sound levels in various environments, providing metrics such as instantaneous
sound levels (**LA**), equivalent continuous sound levels (**LAeq**), and
maximum sound levels (**LAmax**). It also monitors battery levels and RSSI for
reliable operation.

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
4. **Mount the Sensor**: Use mounting kits or tape to install the sensor.

---

## **Step 2: Registering the Sensor on The Things Network (TTN)**

### **2.1 Set Up the LoRaWAN Gateway**
1. Log in to the [TTN Console](https://console.cloud.thethings.network/).
2. Add a gateway:
   - Navigate to **Gateways** > **Add Gateway**.
   - Enter:
     - **Gateway EUI** (found on the gateway label).
     - **Gateway ID** (e.g., `my-lorawan-gateway`).
     - **Frequency Plan** for your region.
   - Click **Register Gateway**.
3. Follow the manufacturer's instructions to configure and connect the gateway.

---

### **2.2 Create a New Application**
1. Navigate to **Applications** > **Add Application** in TTN.
2. Enter:
   - **Application ID**: A unique identifier (e.g., `sound-monitor`).
   - **Description**: (e.g., `Monitoring environmental noise levels`).
   - **Handler**: Select the handler for your region.
3. Generate an **AppEUI** in the application settings.

---

### **2.3 Add a Custom Uplink Payload Formatter**
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
3. Save Changes.

---

## **Step 3: Integrating TTN with Blynk**

### **3.1 Onboarding Using Static Tokens**
1. **Prepare a CSV File**:
   Create a CSV file with the following format to list the device credentials:

   ```csv
   Device EUI,Join EUI,Application Key
   0018B20000000101,70B3D57ED0000010,2B7E151628AED2A6ABF7158809CF4F3C
   0018B20000000102,70B3D57ED0000011,3B7E151628AED2A6ABF7158809CF4F3D
   0018B20000000103,70B3D57ED0000012,4B7E151628AED2A6ABF7158809CF4F3E
   ```

2. **Upload the CSV File**:
   - In Blynk, go to **Developer Zone** > **Static Tokens**.
   - Click **Generate Static Tokens** > **Create From File**.
   - Upload the CSV file.
   - Blynk will generate unique QR codes for each device.

3. **Scan the QR Codes**:
   - Use the Blynk mobile app or web dashboard to scan the QR codes.
   - Once scanned, the devices will be automatically created in Blynk and registered with The Things Stack.

---

### **3.2 Automated Device Onboarding**
1. Enable **Automated Device Onboarding** in Blynk:
   - Go to the application settings in Blynk.
   - Turn on **Enable automated device onboarding**.
   - Specify:
     - **LoRaWAN Version**, **Frequency Plan**, and **Regional Parameter Version**.
     - Enable **Support Class B** and/or **Support Class C** if required.

2. **Provide The Things Stack Details**:
   - Obtain addresses from **Admin Panel** > **Network Information** in The Things Stack.
   - Enter them in Blynk.

3. **Grant Permissions**:
   - Generate a new API key in TTN with:
     - **View device keys in application**.
     - **Create devices in application**.
     - **Edit device keys in application**.

4. Blynk will automatically create metadata fields: **Device EUI**, **Join EUI**, and **AppKey**.

---

### **3.3 Configuring MQTT Integration**
1. **Set Up MQTT in TTN**:
   - Navigate to **Integrations** > **MQTT** in the TTN Console.
   - Copy:
     - **Server Address**: e.g., `eu1.cloud.thethings.network`.
     - **Port**: `1883` (unsecured) or `8883` (secured).
     - **Username**: TTN AppID.
     - **Password**: Generate a new MQTT API key.

2. **Integrate with Blynk**:
   - In Blynk, go to **Developer Zone** > **Integrations** > **The Things Stack**.
   - Enter:
     - **Hostname**: MQTT server address.
     - **Port**: `1883` or `8883`.
     - **Username**: TTN AppID.
     - **Password**: MQTT API key.
   - Click **Connect**.

3. **Test Integration**:
   - Verify the status changes to **Connected** in Blynk.
   - Confirm data appears in the **Devices** section.

---

## **Step 4: Preconfigured Dashboard in Blynk**

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

### **4.2 Setting the Location**
1. Navigate to the **Location** section in the Blynk dashboard.
2. Enter the sensor's address or drag the pin on the map to the correct location.
3. Save the changes to reflect the updated position.

---

### **4.3 Using Automations**
1. Go to the **Automation** section in Blynk.
2. Create a new automation:
   - **Trigger**: Set conditions (e.g., `LAeq > 80 dB`).
   - **Action**: Configure notifications or toggle a device state.
3. Save and test the automation:
   - Simulate events to ensure triggers activate correctly.

---

## **Error Handling and Troubleshooting**
1. **Sensor Issues**:
   - Check battery polarity and charge.
   - Reset the sensor if unresponsive.

2. **Connectivity Problems**:
   - Verify LoRaWAN settings and gateway connection.
   - Test MQTT integration.

3. **Data Issues**:
   - Check the payload formatter in TTN.
   - Debug MQTT connections with tools like MQTT Explorer.

---

[![Watch the video](https://i.sstatic.net/Vp2cE.png)](https://youtu.be/cuykM1xJTrU?feature=shared)




