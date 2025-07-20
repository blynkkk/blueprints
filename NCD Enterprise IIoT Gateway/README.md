## Introduction

This blueprint will guide you through setting up your NCD Enterprise IIoT Gateway to work with Blynk using Wi-Fi, Cellular, or Ethernet connectivity.

## How to Use This Guide

### 1. Unpacking and Initial Setup

#### 1.1 Required Components:
- [NCD Enterprise IIoT Gateway](https://store.ncd.io/product/enterprise-iiot-gateway/)
- Antennas
- Batteries (if applicable)
- Mounting accessories

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

The NCD Enterprise IIoT Gateway offers multiple connectivity options to ensure
reliable communication and data transfer between your IoT devices and the
network. This section covers the setup and configuration for Wi-Fi, Ethernet,
    and LTE interfaces.

#### 2.4.1 Ethernet Configuration

Ethernet provides a stable and fast connection.

1. **Connect Ethernet Cable:**
   - Plug one end of an Ethernet cable into the ETH1 port on the gateway.
   - Plug the other end into your router or network switch.

2. **Power On the Gateway:**
   - Connect the power adapter to the gateway and plug it into a power outlet.
   - The gateway should power on, indicated by the power LED lighting up.

3. **Access the Web Interface:**
   - Open a web browser on a computer connected to the same network.
   - Enter the gateway’s IP address (you can find this in your router’s connected devices list) to access the web interface.

4. **Optional: Static IP Configuration:**
   - If you need a fixed IP for the gateway, navigate to "Network > Ethernet" in the web interface and set a static IP.

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

3. **Disconnect Ethernet Cable:**
   - Once Wi-Fi is set up, you can disconnect the Ethernet cable.

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

![Cellular Settings](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main//Image/cellular.png)

5. **Check LTE Connection:** Verify the LTE connection status in the web configuration interface.

By configuring these connectivity interfaces, you ensure that your gateway is equipped to handle various network scenarios, providing flexibility and reliability for your IoT applications.

#### 2.5 Access Interfaces

1. **Web Configuration:** Access the configuration interface at `http://[domain_or_ip]` using `ncdio` / `ncdB3ast` for login.
   - **Domain Name:** The domain name format is `ncd-xxxx.local`, where `xxxx` are the last 4 characters of the Gateway's MAC address. The MAC address can be found on the side of the device. For example, if the last 4 characters of your Gateway's MAC address are `c398`, the domain name would be `http://ncd-c398.local`.
   - **Network Settings:** Configure static IPs, DNS, and firewall rules as needed.
   - **Customizations:** Set up user accounts, logging, and notifications for specific events.
2. **Node-Red:** Visit `http://[domain_or_ip]:1880` to use Node-Red.
3. **SSH Access:** Connect via SSH with `ncdio` / `ncdB3ast` on port 22.

#### 2.6 Enable SSH:
   - Connect by the ETH or WIFI to the gateway.
   - Open the Gateway's web dashboard at: `http://ncd-xxxx.local`using the credentials `ncdio` / `ncdB3ast`.
     - Go to **Service** > **SSH**.
     - Turn **ON** SSH, then click **Submit** and **Apply**.

![SSH](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%20Environmental%20Air%20Quality%20Sensor/Image/dashboard-ncdio.png)

### 3. Preparing Your Device in Blynk.Cloud

1. **Use the Sensor Blueprint:** Click the **Use Blueprint** button.
2. **Activate the Device:** On the right panel, click the **Activate Device** button.
3. **Generate AuthToken:** Click the **Generate AuthToken** button. You'll need the generated AuthToken for the next step. Click button **Next**.
> **Note:** Record the device credentials shown in the upper right corner for use in the next step.

### 4. Accessing Node-RED on the Gateway

1. Open a web browser and navigate to `http://[domain_or_ip]:1880`.
2. Log in to the Node-RED dashboard.

### 5. Configuring the Node-RED Flow

1. Copy or download the firmware flow file from second step of device activation into Node-RED.
   - In Node-RED, press **CTRL + I** or use the menu to select **Import**.
   - Paste the copied code or upload the flow file (.json).

 Your flow should look like this:

![Node-RED Flow](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main//Image/flow.png)

2. **Set Up MQTT:**
   - Click on any of the highlighted MQTT-out node.

	![MQTT Out](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main//Image/flow-arrow.png)

   - Select the highlighted icon.

	![MQTT Property](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%201%20Channel%20Vibration%20Sensor%20Plus/Image/mqtt-property.jpg)

   - Go to the Security tab.

	![Broker Property](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%201%20Channel%20Vibration%20Sensor%20Plus/Image/broker-property.png)

   - Enter the AuthToken generated by Blynk as a password for your device (use “device” as the username).

	![Security Tab](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%201%20Channel%20Vibration%20Sensor%20Plus/Image/security-tab.png)

### Step 6: Running the Sample Using Node-RED

1. **Deploy the Flow:**
   - Click the **Deploy** button in Node-RED to activate the flow. When flow connect to cloud status by the mqtt node will have green color and have text "Connected".

2. **Test Your Setup:**
   - Go to Blynk.cloud to check the sensor data and verify everything is working.
    The **NCD Enterprise IIoT Gateway Dashboard** provides a comprehensive overview
    of the device's operational status, connectivity, and resource utilization.

    ![Dashboard](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-Gateway/NCD%20Enterprise%20IIoT%20Gateway/Image/screenshot-1.png)

    It includes the following key sections:

    1. **General Information:**
       - Displays device status (ON/OFF), uptime duration, and the assigned IP address.

    2. **Connectivity:**
       - Shows active network link (Ethernet/Wi-Fi), data transmission statistics (RX/TX bytes), and cellular status, indicating whether SIM cards are detected.

    3. **Usage Metrics:**
       - Real-time RAM usage, storage capacity, and CPU utilization.

    4. **System Information:**
       - Displays Linux kernel version and system build details.

    5. **CPU Temperature:**
       - A visual gauge displays the current CPU temperature, helping monitor thermal performance.

    The dashboard allows users to track system performance, troubleshoot connectivity issues, and ensure the gateway operates optimally for IoT applications.

    The Blynk mobile app provides the same functionality as the web dashboard, allowing you to monitor and manage your system on the go. You can access real-time data, view historical trends, and configure notification thresholds directly from your mobile device. This ensures continuous monitoring and timely alerts, helping you maintain optimal system performance anytime, anywhere.


    To add a new gateway, you need to repeat this guide for the new device.

🎥 **Watch the Video Guide**
[![Watch the video](https://img.youtube.com/vi/EbJnY5h65DE/maxresdefault.jpg)](https://youtu.be/EbJnY5h65DE)

## Next Steps

- Explore the Blynk Web Console and Blynk IoT app, and try monitoring your gateway data.
- Read the Blynk Documentation to learn how to work with Virtual Pins.
- [Learn more about Automations.](https://docs.blynk.io/en/concepts/automations)
- [Discover how to Share Devices with other users.](https://docs.blynk.io/en/blynk.console/devices/device-sharing)
- Customize the code to meet your specific needs.
- Add some sensors or devices to your setup.

## Troubleshooting

- Ensure you have the latest versions of the software you are using.
- Verify that all libraries are up to date.
- Check that all dependencies and configurations are correct.
- Inspect your code for errors.

### Common Issues:

1. **Connection Problems:**
   - Check network settings and firewall rules.
   - Verify the gateway's network connection.

2. **Node-RED Issues:**
   - **Flow Not Deploying:** Check for syntax errors or missing nodes.
   - **MQTT Connection Failure:** Verify MQTT broker settings and credentials.

## Related Links

- [Blynk MQTT API documentation](https://docs.blynk.io/en/hardware-guides/mqtt-api)
- [Blynk Troubleshooting guide](https://docs.blynk.io/en/getting-started/troubleshooting)
- [Blynk Documentation](https://docs.blynk.io/en/)
- [Blynk NodeRED Documentation](https://docs.blynk.io/en/hardware-guides/node-red)
- [Node-RED Documentation](https://nodered.org/docs/getting-started/local)
- [NCD Support](https://ncd.io/contact/)
- [RT090 HM EG5120 V1.0.2 Documentation](https://www.davantel.com/wp-content/uploads/2023/06/RT090_HM_EG5120_V1.0.2.pdf)
- [RobustOS Software Manual V1.0.0](https://rjconnect.co.za/wp-content/uploads/2022/12/RT_SM_RobustOS-Software-Manual_V1.0.0.pdf)

By following this guide, you can effectively set up and utilize your NCD Enterprise IIoT Gateway for various IoT applications.

