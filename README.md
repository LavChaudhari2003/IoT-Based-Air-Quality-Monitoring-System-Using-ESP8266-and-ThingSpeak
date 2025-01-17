# IoT-Based-Air-Quality-Monitoring-System-Using-ESP8266-and-ThingSpeak


This project implements an air quality monitoring system using an ESP8266 WiFi module, various sensors, and the ThingSpeak platform. The system measures environmental parameters such as CO2, temperature, humidity, CO, LPG, and smoke levels, providing real-time data and insights into air quality.

## Features
- **Multi-Parameter Measurement**: Monitors CO2, temperature, humidity, CO, LPG, and smoke levels.
- **ThingSpeak Integration**: Updates sensor readings to a cloud platform for real-time monitoring and visualization.
- **WiFi Connectivity**: Uses an ESP8266 WiFi module for seamless data transmission.
- **Dynamic Status Updates**: Provides insights based on measured parameters.

## Hardware Requirements
1. Arduino board
2. ESP8266 WiFi module
3. MQ135 sensor (CO2 measurement)
4. MQ2 sensor (CO, LPG, and smoke measurement)
5. DHT sensor (temperature and humidity measurement)
6. Breadboard and jumper wires
7. Power supply

## Software Requirements
- Arduino IDE
- ThingSpeak account for data visualization

## Setup and Usage
1. **Hardware Setup**:
   - Connect the sensors (MQ135, MQ2, and DHT) to the specified pins on the Arduino board.
   - Ensure the ESP8266 module is connected to pins 6 and 7 for RX and TX, respectively.

2. **Software Configuration**:
   - Clone the repository and open the project in the Arduino IDE.
   - Install the necessary libraries (`MQ135`, `MQ2`, `DHT`, `WiFiEsp`, and `ThingSpeak`).
   - Update the following variables with your WiFi and ThingSpeak credentials:
     ```cpp
     char ssid[] = "Your_SSID";
     char pass[] = "Your_PASSWORD";
     unsigned long myChannelNumber = 1915100; // Your ThingSpeak channel number
     const char *myWriteAPIKey = "Your_API_Key";
     ```

3. **Upload Code**:
   - Upload the code to your Arduino board using the Arduino IDE.

4. **Monitor Data**:
   - Open the ThingSpeak channel to view real-time air quality data.
   - Use the serial monitor to debug and view status messages.

## Output
The system provides the following outputs:
- CO2 concentration (ppm)
- Temperature (°C)
- Humidity (%)
- Carbon monoxide (ppm)
- LPG concentration (ppm)
- Smoke level (ppm)


## Applications
- Indoor air quality monitoring
- Industrial safety monitoring
- Environmental data collection
- Smart city infrastructure

## Guide
- **Supervisor**: Dr. Biswajit Mishra



