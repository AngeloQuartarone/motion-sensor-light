# motion-sensor-light --- Arduino MQTT Light Control

## Description
This Arduino project is designed to control a smart bult via MQTT based on sensor input and a button press. The project uses an Arduino board with WiFi capabilities to connect to an MQTT broker and send status updates about the light behavior.

## Features
- **WiFi Connectivity**: Connects to a WiFi network to communicate with an MQTT broker
- **MQTT Communication**: Sends messages to an MQTT broker to indicate which action trigger
- **Sensor Input**: Uses a motion sensor to determine when the light should be turned on or off
- **Button Control**: Toggles an "always-on" mode for the light, making the value of the motion sensor irrelevant in order to control it with other source (in my case Alexa)

## Requirements
- **Arduino Board with WiFi Capabilities**: Such as the Arduino Uno R4 (that I used) or similar
- **Smart bulb**
- **MQTT Broker**: An MQTT server for receiving messages. This example uses a broker in a Home Assistant instance running on Raspberry Pi 3
- Arduino IDE: For uploading the code to the Arduino board
- Arduino libraries:
  - **WiFiS3** for WiFi connectivity
  - **ArduinoMqttClient** for MQTT communication
  - **arduino_secrets.h** (ensure to create this file with your network credentials)


## Installation
1. Install Arduino IDE: Download and install the Arduino IDE from arduino.cc
2. Install Required Libraries: Open the Arduino IDE and navigate to Sketch > Include Library > Manage Libraries. Search for and install the following libraries: 
   - WiFiS3
   - ArduinoMqttClient
3. Configure Network Credentials:
    - Create a file named arduino_secrets.h in the same directory as your main sketch
    - Add your WiFi credentials to arduino_secrets.h:  
    ```c++
    #define SECRET_SSID "your-SSID"
    #define SECRET_PASS "your-PASSWORD"
    ```
## Usage
1. Power On: Connect the Arduino to a power source. It will attempt to connect to the specified WiFi network and MQTT broker
2. Sensor and Button Interaction:
   - The motion sensor is connected to WAKEUP_PIN (pin 6). When motion is detected (sensor value HIGH), the light will be turned on by sending to the mqtt broker special string (in this case "light" to trigger the light on behavior and "nolight" to turn it off)
   - The button is connected to BUTTON (pin 7). Pressing the button toggles the alwaysOn state. When alwaysOn is active, the light will stay on regardless of the sensor input




