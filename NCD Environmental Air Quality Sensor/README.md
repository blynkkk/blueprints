## Introduction

This blueprint will guide you through launching your project with the Industrial IoT Long Range Wireless Environmental Temperature, Humidity, Pressure, and Air Quality Sensor.

The sample project consists of the sensor, which measures temperature,
humidity, pressure, and air quality, and transmits these measurements wirelessly
to the NCD Enterprise IIoT Gateway.

## How To Use This Blueprint

### 1. Unpacking and Initial Setup

#### 1.1 Required Components:
- [Industrial IoT Long Range Wireless Environmental Temperature, Humidity, Pressure, and Air Quality Sensor](https://store.ncd.io/product/industrial-iot-long-range-wireless-environmental-temperature-humidity-pressure-air-quality-sensor/)
- One of the NCD Gateway options:
    - [NCD Enterprise IIoT Gateway](https://store.ncd.io/product/enterprise-iiot-gateway/)
    - [Enterprise IIoT Gateway Lite](https://store.ncd.io/product/enterprise-iiot-gateway-lite/)
- Antennas
- Batteries (if applicable)
- Mounting accessories

Verify that you have all necessary parts. For detailed instructions on unpacking and initial setup, refer to the [drawing tab](https://store.ncd.io/product/industrial-iot-long-range-wireless-environmental-temperature-humidity-pressure-air-quality-sensor/#drawing) on the product page.

### 2. Configuring the NCD Enterprise IIoT Gateway

#### 2.1 Required Components:
- NCD Enterprise IIoT Gateway
- Antennas

The NCD Enterprise IIoT Gateway facilitates seamless integration and communication between various IoT devices and networks.

#### 2.2 Hardware Setup

1. **Connect Terminal Connectors:** Insert the terminal connectors into their designated ports.
2. **Attach Antennas:**
   - **WiFi and DigiMesh Antennas:** Install these into the appropriate ports.
   - **LTE Antennas (Optional):** If using LTE, attach the antennas and insert the SIM card.
3. **Connect to ETH1:** Use an Ethernet cable to link the ETH1 port to a DHCP router for automatic IP assignment.
4. **Power Supply:** Connect the power supply to the gateway and ensure it powers on.

#### 2.3 Preparation

1. **SIM Card:**
   - Ensure the SIM card is activated with data services enabled.
   - Verify network coverage and signal strength in your area.
2. **Safety Precautions:**
   - Power off the gateway before inserting the SIM card to avoid damage.
   - Handle antennas carefully to avoid damaging the connectors.

#### 2.4 Connectivity Interfaces

The NCD Enterprise IIoT Gateway offers multiple connectivity options to ensure reliable communication and data transfer between your IoT devices and the network. This section covers the setup and configuration for Wi-Fi, Ethernet, and LTE interfaces.

#### 2.4.1 Ethernet Configuration

The gateway supports Ethernet connectivity for stable and high-speed data transmission.

1. **Connect to ETH1:** Use an Ethernet cable to connect the ETH1 port on the gateway to a DHCP-enabled router for automatic IP assignment.
2. **Static IP Configuration (Optional):**
   - Access the web configuration interface.
   - Navigate to "Network > Ethernet" and set a static IP if required for your network setup.

#### 2.4.2 Wi-Fi Configuration

The gateway can function in both Wi-Fi Access Point (AP) and Client modes, with AP mode as the default setting.

1. **Configure Router as Wi-Fi AP:**
   - Click “Interface > Wi-Fi > Wi-Fi” in the web configuration interface.
   - Select “AP” as the mode and click “Submit”.
   - Note that only 2.4GHz Wi-Fi is supported.

2. **Switch to Client Mode:**
   - If you need the gateway to connect to an existing Wi-Fi network, select “Client” as the mode.
   - Enter the SSID and password of the Wi-Fi network you wish to connect to.
   - Click “Submit” to save the settings.

#### 2.4.3 LTE Configuration

For locations where wired or Wi-Fi connections are impractical, the gateway can connect via LTE.

1. **Insert SIM Card:** Ensure the SIM card is properly inserted into the designated slot.
2. **Attach LTE Antennas:** Securely connect the LTE antennas to the marked ports on the gateway.
3. **Login to the Device:**
   - Connect the gateway’s Ethernet port to a PC with a standard Ethernet cable.
   - Configure the PC with a static IP address on the same subnet as the gateway. Use the following settings:

    ```
    IP address: 192.168.0.2
    Subnet mask: 255.255.255.0
    Default gateway: 192.168.0.1
    Preferred DNS server: 8.8.8.8
    ```
    - Open a web browser and navigate to the gateway's IP address.
    - Login using the credentials provided in the [device documentation](https://www.davantel.com/wp-content/uploads/2023/06/RT090_HM_EG5120_V1.0.2.pdf).

4. **Configure Cellular Settings:**
    - Navigate to the "Network -> Cellular" section in the web interface.
    - Enter the APN settings provided by your LTE service provider.
    - Save the settings and reboot the gateway if necessary.

| **Parameter**        | **Description**                                         |
|----------------------|---------------------------------------------------------|
| **APN**              | Access Point Name provided by the LTE service provider. |
| **Username**         | Username for the APN (if required).                     |
| **Password**         | Password for the APN (if required).                     |
| **Dial Number**      | Usually `*99#` for most networks.                       |
| **Authentication**   | Type of authentication (e.g., PAP, CHAP).               |

![Cellular Settings](https://raw.githubusercontent.com/khrystynaO/blueprints/khrystynaO/feature/NCD/NCD%20Environmental%20Air%20Quality%20Sensor/Image/cellular.png)

5. **Check LTE Connection:** Verify the LTE connection status in the web configuration interface.

By configuring these connectivity interfaces, you ensure that your gateway is equipped to handle various network scenarios, providing flexibility and reliability for your IoT applications.

#### 2.5 Access Interfaces

1. **Web Configuration:** Access the configuration interface at `http://[domain_or_ip]` using `ncdio` / `ncdB3ast` for login.
   - **Domain Name:** The domain name format is `ncd-xxxx.local`, where `xxxx`
   are the last 4 characters of the Gateway's MAC address. The MAC address can
   be found on the side of the device. For example, if the last 4 characters of
   your Gateway's MAC address are `c398`, the domain name would be `http://ncd-c398.local`.
   - **Network Settings:** Configure static IPs, DNS, and firewall rules as needed.
   - **Customizations:** Set up user accounts, logging, and notifications for specific events.
2. **Node-Red:** Visit `http://[domain_or_ip]:1880` to use Node-Red.
3. **SSH Access:** Connect via SSH with `ncdio` / `ncdB3ast` on port 22.

### 3. Preparing Your Device in Blynk.Cloud

1. Click the **`Use Blueprint`** button in the [NCD Environmental Air Quality Sensor](https://blynk.cloud/dashboard/blueprints/Library/TMPL49toG3xmD).
2. In the left panel, select **Devices**.
3. Click **New Device**.
4. Choose **From Template -> NCD Environmental Air Quality Sensor**, and click **Create**.

> **Note:** Record the device credentials shown in the upper right corner for use in the next step.

### 4. Accessing Node-RED on the Gateway

1. Open a web browser and navigate to `http://[domain_or_ip]:1880`.
2. Log in to the Node-RED dashboard.

### 5. Configuring the Node-RED Flow

1. Copy and import the [flow file](https://raw.githubusercontent.com/khrystynaO/blueprints/khrystynaO/feature/NCD/NCD%20Environmental%20Air%20Quality%20Sensor/Firmware/flow.json) into Node-RED.
2. Open settings for the MQTT node and update the server properties:
   - Go to the Security tab.
   - Enter your [Blynk device credentials](https://docs.blynk.io/en/getting-started/activating-devices/manual-device-activation#getting-auth-token) in the Password field, and use "device" for the Username field.
   For more details, refer to the [Blynk Node-RED guide](https://docs.blynk.io/en/hardware-guides/node-red#configure-the-mqtt-broker) **Configure the MQTT Broker** topic.

![Node-RED Flow](https://raw.githubusercontent.com/khrystynaO/blueprints/khrystynaO/feature/NCD/NCD%20Environmental%20Air%20Quality%20Sensor/Image/flow.png)

### 6. Running the Sample Using Node-RED

Deploy the flow and use Blynk.cloud for testing.

## Next Steps

- Explore the Blynk Web Console and Blynk IoT app, and try monitoring your sensor data from both.
- Read the Blynk Documentation to learn how to work with Virtual Pins.
- [Learn more about Automations.](https://docs.blynk.io/en/concepts/automations)
- [Discover how to Share Devices with other users.](https://docs.blynk.io/en/blynk.console/devices/device-sharing)
- Customize the code to meet your specific needs.
- Add more sensors or devices to your setup.

## Troubleshooting

- Ensure you have the latest versions of the software you are using.
- Verify that all libraries are up to date.
- Check that all dependencies and configurations are correct.
- Inspect your code for errors.

### Common Issues:

1. **Connection Problems:**
   - Ensure the sensor is powered and within range.
   - Check network settings and firewall rules.
   - Verify the gateway's network connection.

2. **Calibration Errors:**
   - Follow the software instructions to recalibrate the sensor.
   - Ensure the environment is stable during calibration.

3. **Node-RED Issues:**
   - **Flow Not Deploying:** Check for syntax errors or missing nodes.
   - **MQTT Connection Failure:** Verify MQTT broker settings and credentials.

## Related Links

- [Blynk MQTT API documentation](https://docs.blynk.io/en/hardware-guides/mqtt-api)
- [Blynk Troubleshooting guide](https://docs.blynk.io/en/getting-started/troubleshooting)
- [Blynk Documentation](https://docs.blynk.io/en/)
- [Blynk NodeRED Documentation](https://docs.blynk.io/en/hardware-guides/node-red)
- [NCD Wireless Environmental Sensor Documentation](https://ncd.io/blog/wireless-environmental-sensor-product-manual/)
- [Node-RED Documentation](https://nodered.org/docs/getting-started/local)
- [NCD Support](https://ncd.io/contact/)
- [RT090 HM EG5120 V1.0.2 Documentation](https://www.davantel.com/wp-content/uploads/2023/06/RT090_HM_EG5120_V1.0.2.pdf)
- [RobustOS Software Manual V1.0.0](https://rjconnect.co.za/wp-content/uploads/2022/12/RT_SM_RobustOS-Software-Manual_V1.0.0.pdf)

By following this blueprint, you can effectively set up and utilize your NCD Wireless Environmental Sensor for various IoT applications.

