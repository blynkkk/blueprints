# **Miromico Miro Insight - Environmental Sensor Blueprint Guide**

The Miromico miro Insight Lux is a compact battery-powered batteryless LoRaWAN
device equipped with a temperature sensor and humidity sensor.
It’s designed for real-time environmental monitoring and magnetic field
detection, transmitting data over LoRaWAN networks. This guide provides
step-by-step instructions to set up the sensor, register it with The Things
Network (TTN), and integrate it with Blynk IoT for data visualization and
control.

# **Step 1: Unpacking and Initial Setup**

## **1.1 Required Components**
- **Miromico Miro Insight Sensor**
- **LoRaWAN Gateway** connected to TTN
- **Activation Magnet** (for waking up the device)

## **1.2 Initial Setup**
1. **Verify Package Contents:** Ensure the sensor, documentation, and accessories are included and undamaged.
2. **Wake Up the Device:**
   - Hold the magnet near the activation point of the device for a few seconds.
   - The LED should blink to confirm the device is active.
3. **Check Battery:** Pre-installed. No need for manual installation.

> **Note:** Miro Insight devices are preconfigured and activated via **magnet** instead of a physical power button. [miro Insight Lux Quickstart](https://www.youtube.com/watch?v=UtzS1Sdv6ms).

# **Step 2: Prepare The Things Network (TTN) for integration**

## **2.1 Setting Up the LoRaWAN Gateway**

1. **Log in to the TTN Console:** Visit the [TTN Console](https://console.cloud.thethings.network/).
2. **Add a Gateway:**
   - Navigate to **Gateways** > **Add Gateway**.
   - Enter:
     - **Gateway EUI** (found on the gateway label)
     - **Gateway ID** (e.g., `my-lorawan-gateway`)
     - **Frequency Plan** for your region (see the table below)
   - Click **Register Gateway**.
3. **Configure the Gateway:**
   - Follow the manufacturer's instructions to connect the gateway to TTN.
   - Ensure the gateway is online and visible in the TTN Console.

![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/gateway.png)

**Frequency Plans**
| **Frequency Plan** | **Region**            | **Description**                                                                 |
|--------------------|-----------------------|---------------------------------------------------------------------------------|
| **EU868**          | Europe                | Operates at 868 MHz. Commonly used across the EU for LoRaWAN deployments.       |
| **US915**          | North America         | Operates at 915 MHz. Used in the United States, Canada, and Mexico.             |
| **AS923**          | Asia-Pacific          | Operates at 923 MHz. Covers countries like Japan, Australia, and New Zealand.   |
| **IN865**          | India                 | Operates at 865 MHz. Dedicated plan for deployments in India.                   |
| **AU915**          | Australia/New Zealand | Operates at 915 MHz. Preferred for LoRaWAN in Australia and New Zealand.        |
| **KR920**          | South Korea           | Operates at 920 MHz. Allocated specifically for South Korea.                    |
| **RU864**          | Russia                | Operates at 864 MHz. Used exclusively within Russia.                            |

Follow TTN’s Gateway setup guide to ensure your gateway is online.

## **2.2 Creating a New Application in TTN**

1. In the [TTN Console](https://console.cloud.thethings.network/) navigate to **Applications → Add Application**.
2. Fill in:
   - **Application ID:** (e.g., `miro-insight-environmental-monitoring`)
   - **Description:** (Optional)
3. **Create Application**.

![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/create-form.png)

> **Note:**
> To ensure smooth operation, it’s recommended that all devices within a TTN
> application are of the same sensor type (e.g., miro insight lux). If you’d like > to use different types of sensors, consider creating a separate application for
> each sensor type. This helps maintain better compatibility and performance.

## **2.3 Setting Up the application Payload Formatter**

1. Open the created application and, from the left-hand menu, select **Payload Formatters**.

![Formater](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/formatter.png)

2. Select the **Uplink** tab and choose **Custom JavaScript Formatter**.
3. Paste the following formatter code and click **Save Changes**:

```javascript

function signed(value, size) {
    const mask = 1 << (size * 8 - 1);
    const buf = -(value & mask) + (value & ~mask);
    return buf;
}

function toHexString(byteArray) {
    let s = '';
    byteArray.forEach(function(byte) {
        s += ('0' + (byte & 0xFF).toString(16)).slice(-2);
    });
    return s;
}

function decodeUplink(input) {
    const bytes = input.bytes;
    const port = input.fPort;

    const decoded = {};
    const warnings = [];
    const errors = [];
    const output = { data: {} };

    if (port === 15) {
        let idx = 0;
        const total = bytes.length;

        while (idx < total) {
            const length = bytes[idx];

            switch (bytes[idx + 1]) {
                case 1: { // Temperature and Humidity
                    let start = idx + 2;
                    let tempArr = [];
                    let humArr = [];
                    while (start < idx + length) {
                        tempArr.push(
                            signed(bytes[start] + bytes[start + 1] * 256, 2) / 100
                        );
                        humArr.push(bytes[start + 2] / 2);
                        start += 3;
                    }
                    decoded.temperature = tempArr.length === 1 ? tempArr[0] : tempArr;
                    decoded.humidity = humArr.length === 1 ? humArr[0] : humArr;
                    break;
                }

                case 2: { // CO2
                    let start = idx + 2;
                    let co2Arr = [];
                    while (start < idx + length) {
                        co2Arr.push(bytes[start] + bytes[start + 1] * 256);
                        start += 2;
                    }
                    decoded.co2 = co2Arr.length === 1 ? co2Arr[0] : co2Arr;
                    break;
                }

                case 5: { // Common Settings
                    decoded.settings_cycle = bytes[idx + 2] + bytes[idx + 3] * 256;
                    decoded.settings_tx_interval = bytes[idx + 4];
                    decoded.settings_cfm = Boolean(bytes[idx + 5] & 0x80);
                    decoded.settings_led = Boolean(bytes[idx + 5] & 0x40);
                    decoded.settings_adr = Boolean(bytes[idx + 5] & 0x20);
                    decoded.settings_continous_iaq = Boolean(bytes[idx + 5] & 0x10);
                    decoded.settings_rpt_int = Boolean(bytes[idx + 5] & 0x08);
                    decoded.settings_nbretrans = bytes[idx + 6] & 0x0f;
                    break;
                }

                case 6: { // CO2 Settings
                    decoded.settings_co2_subsamples =
                        bytes[idx + 4] + bytes[idx + 5] * 256;
                    decoded.settings_co2_abc_period =
                        bytes[idx + 6] + bytes[idx + 7] * 256;
                    break;
                }

                case 9: { // Battery
                    decoded.battery_v = (bytes[idx + 2] + bytes[idx + 3] * 256) / 100;
                    break;
                }

                case 10: { // Firmware Hash
                    decoded.git_hash = toHexString(
                        bytes.slice(idx + 2, idx + 6).reverse()
                    );
                    break;
                }

                case 11: { // Door Alarm Set
                    decoded.door_alarm = true;
                    decoded.open_counter =
                        bytes[idx + 2] +
                        bytes[idx + 3] * 256 +
                        bytes[idx + 4] * 256 * 256 +
                        bytes[idx + 5] * 256 * 256 * 256;
                    decoded.alarm_counter = bytes[idx + 6] + bytes[idx + 7] * 256;
                    decoded.settings_alarm_time_s = bytes[idx + 8] + bytes[idx + 9] * 256;
                    break;
                }

                case 12: { // Door Alarm Clear
                    decoded.door_alarm = false;
                    decoded.open_counter =
                        bytes[idx + 2] +
                        bytes[idx + 3] * 256 +
                        bytes[idx + 4] * 256 * 256 +
                        bytes[idx + 5] * 256 * 256 * 256;
                    decoded.alarm_counter = bytes[idx + 6] + bytes[idx + 7] * 256;
                    break;
                }

                case 13: { // Door Status
                    decoded.open_counter =
                        bytes[idx + 2] +
                        bytes[idx + 3] * 256 +
                        bytes[idx + 4] * 256 * 256 +
                        bytes[idx + 5] * 256 * 256 * 256;
                    decoded.alarm_counter = bytes[idx + 6] + bytes[idx + 7] * 256;
                    decoded.door_alarm = Boolean(bytes[idx + 8]);
                    break;
                }

                case 14: { // Alarm Settings
                    decoded.settings_alarm_time_s = bytes[idx + 2] + bytes[idx + 3] * 256;
                    decoded.settings_hall_debounce_ms =
                        bytes[idx + 4] + bytes[idx + 5] * 256;
                    decoded.settings_door_status_time_s =
                        bytes[idx + 6] +
                        bytes[idx + 7] * 256 +
                        bytes[idx + 8] * 256 * 256 +
                        bytes[idx + 9] * 256 * 256 * 256;
                    break;
                }

                case 15: { // IAQ
                    let start = idx + 2;
                    let iaqArr = [];
                    let iaqAccArr = [];
                    while (start < idx + length) {
                        iaqArr.push(bytes[start] + (bytes[start + 1] & 0x3f) * 256);
                        iaqAccArr.push(bytes[start + 1] >> 6);
                        start += 2;
                    }
                    decoded.iaq = iaqArr.length === 1 ? iaqArr[0] : iaqArr;
                    decoded.iaq_accuracy = iaqAccArr.length === 1 ? iaqAccArr[0] : iaqAccArr;
                    break;
                }

                case 16: { // Pressure
                    let start = idx + 2;
                    let pressureArr = [];
                    while (start < idx + length) {
                        pressureArr.push(
                            bytes[start] +
                            bytes[start + 1] * 256 +
                            bytes[start + 2] * 256 * 256
                        );
                        start += 3;
                    }
                    decoded.pressure = pressureArr.length === 1 ? pressureArr[0] : pressureArr;
                    break;
                }

                case 17: { // Reported Interval
                    decoded.reported_interval = bytes[idx + 2] + bytes[idx + 3] * 256;
                    break;
                }

                case 20: { // Light
                    decoded.light = bytes[idx + 2] + bytes[idx + 3] * 256;
                    break;
                }

                case 21: { // Conditional TX thresholds
                    decoded.settings_cond_tx_co2_th = bytes[idx + 2] + bytes[idx + 3] * 256;
                    decoded.settings_cond_tx_temp_th = bytes[idx + 4] + bytes[idx + 5] * 256;
                    decoded.settings_cond_tx_hum_th = bytes[idx + 6] + bytes[idx + 7] * 256;
                    break;
                }

                case 22: {
                    decoded.settings_blind_adr_profile = bytes[idx + 2];
                    break;
                }

                case 23: {
                    decoded.settings_light_interval = bytes[idx + 2];
                    break;
                }

                default:
                    warnings.push("Unknown message type: " + bytes[idx + 1]);
                    break;
            }

            idx += length + 1;
        }
    } else {
        errors.push("Uplink is not on port 15");
    }

    if (warnings.length > 0) {
        decoded.warnings = warnings;
    }

    if (errors.length > 0) {
        decoded.errors = errors;
    }

    output.data = decoded;
    return output;
}

```

4. Select the Downlink tab and choose Custom JavaScript Formatter.
5. Paste the following formatter code and click Save Changes.

```javascript

function encodeDownlink(input) {
  const output = {
    bytes: [],
    fPort: 3,    // fPort is 3 as you said
    warnings: [],
    errors: []
  };

  // Use input.data if available
  const commandInput = input.data ? input.data : input;

  try {
    if (commandInput.name === "reporting_interval") {

      const measurementInterval = commandInput.value; // only user input
      if (measurementInterval !== 0) {
        // Hardcoded values
        const sendCycle = 0;        // Send after 1 measurement
        const flagsByte = 0x28;     // No confirmation, LED off, ADR on, VOC off, Report interval on
        const retransmissions = 0;  // 3 retransmissions

        // Build the packet
        output.bytes.push(0x06);  // Length
        output.bytes.push(0x87);  // Type

        output.bytes.push(measurementInterval & 0xFF);            // Measurement interval LSB
        output.bytes.push((measurementInterval >> 8) & 0xFF);     // Measurement interval MSB

        output.bytes.push(sendCycle);                             // Send cycle (hardcoded)
        output.bytes.push(flagsByte);                             // Flags (hardcoded)
        output.bytes.push(retransmissions & 0x0F);                // Retransmissions (hardcoded)
      }
    } else {
      output.errors.push("Unsupported command: " + JSON.stringify(commandInput));
    }
  } catch (err) {
    output.errors.push("Encoding error: " + err.message + ". Input: " + JSON.stringify(commandInput));
  }

  return output;
}

function decodeDownlink(input) {
  return {
    data: {
      bytes: input.bytes
    },
    warnings: [],
    errors: []
  };
}

```

## **2.4 Adding the Sensor as an End Device in TTN**

> **Important:** Miromico is simple — all settings are preprogrammed unless  manually reconfigured via LoRaWAN MAC commands.

1. Go to [Miromico LoRaWAN Device Credentials Database](https://deveui.miromico.ch/uuid) and get cred for add your dev into TTN.

2. In the TTN console, select your application (created in step 2.2) and click **Register End Device**.
3. Choose **Enter end device specifics manually**:
   - **Frequency plan**: for your region (see the table below)
   - **LoraWAN version**: provided by the manufacture.

![End dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/end-dev-1.png)

4. Enter:
   - **DevEUI** - provided by the manufacture
   - **JoinEUI (AppEUI)** - provided by the manufacture
   - **AppKey** - provided by the manufacture
   - A unique **End Device ID**
5. Click **Register Device**

![End dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/end-dev-2.png)

> You can find the keys and DevEUI by following the URL or scanning the QR code to access the web page. Enter the code provided on the box, and you will be able to download the keys and other information

## **2.5 Setting Up MQTT Integration**

1. Open created application in TTN.
2. Navigate to TTN Integration Settings:
   - In the TTN Console, open your application and select **Integrations**.
3. Select MQTT:
   - Click **MQTT** from the available integration options.
4. You’ll need these details to set up the MQTT integration in Blynk:
   - **Server Address**
   - **Port**
   - **Username**
   - **Password**: Click **Generate new API key** and copy the generated key. Copy  and keep it secure.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/integarion-mqtt-key.png)


# **Step 3: Prepare Blynk side integration**

1. In **Blynk Console**:
   - Click **Use Blueprint**.
   - Go to **Developer Zone → Integrations → The Things Stack → Add**.
2. Choose the **Miro Insight Lux** template.

![Add intefration](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/add.png)

3. Fill in value copied from step 2.5:
   - **MQTT Server** (e.g., `eu1.cloud.thethings.network:8883`)
   - **Username**
   - **Password**
4. Click **Connect**.

![Connect](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/connect.png)


# **Step 4: Activating the Sensor**

- Use the **magnet** to wake up the sensor and now wait for this sensor connect to gateway.


# **Step 5: Onboarding the Sensor to Blynk**

You can onboard the sensor in two ways:

1. **Automatic Device Creation – Recommended**
   As soon as the sensor sends data to TTN, it will automatically appear on the Blynk Cloud.

![dev online](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/dev-online.png)

2. **Manual Device Creation – If Something Goes Wrong**
   - Navigate to **Devices** → **Create Device**, and select the **miro insight lux** template.
   - In the **Info & Metadata** tab, enter the **TheThingsNetwork Device** field using the device name from TTN.

![TTN-dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/ttn-dev.png)
![TTN-dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/ttn-dev-in-ttn.png)
![TTN-dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/ttn-dev-fill-1.png)
![TTN-dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/ttn-dev-fill.png)

# **Step 6: Monitoring and Analyzing Data**

The dashboard is preconfigured, providing an intuitive interface for real-time monitoring. Both web and mobile dashboards offer the same functionality.

In this dashboard, you can monitor the air quality, temperature, humidity, CO₂ levels, pressure, light intensity, battery voltage, and view historical data. Additionally, you can change the reporting interval by selecting or entering your desired value in seconds.

In the case of Miromico devices, there are many configuration variants. For example, some devices may not send IAQ data, while others may include a Hall sensor or different sensor sets. This formatter is designed to support all such variations.

You can also customize the dashboard to match your specific use case.

# **Step 7: Alerts & Automations**

1. In the Blynk Console, open **Automations**.
2. Create triggers based on **Device State** or **Sensor Value**.

- Example: If **humidity > 80%**, send notification.
- Example: If **battery voltage < 2.8V**, send low battery alert.

# **Step 8: Adding Location in Blynk**

1. Navigate to the **Location** section in Blynk.
2. Enter the address or drag the map pin to the correct location.

![Location](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/location-2.png)

3. Click **Save**.
4. In the device's **Info & Metadata**, assign the saved location.

![Location](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/location-3.png)
![Location](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/location-3.2.png)
![Location](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/miro-Insight-Lux/Images/location-4.png)


# **Step 9: Error Handling and Troubleshooting**

### **9.1 Common Issues**
- **Sensor Not Responding**: Check battery orientation and charge. Try a reset.
- **No Connectivity**: Recheck gateway setup and frequency plan.
- **Missing Data**: Update your **Payload Formatter** in TTN’s Uplink/Downlink settings.

# **Next Steps**
- Explore the Blynk Web Console and mobile app.
- Review [Blynk’s Virtual Pins documentation](https://docs.blynk.io/en/blynk.console/templates/datastreams).
- [Share devices with other users](https://docs.blynk.io/en/blynk.console/devices/device-sharing).
- Customize the integration for your own use case.
- Try onboarding the sensor using static tokens.

