# Smart-Home-Monitoring-System-using-IOT

📡 IoT Sensor Monitoring with ESP8266, ThingSpeak & Web Interface
This project reads distance, temperature, humidity, and light intensity using an HC-SR04 Ultrasonic Sensor, DHT11, and LDR, then sends the data to ThingSpeak for visualization. It also serves data on a local web interface via the ESP8266.

📦 Components Used

1.ESP8266 NodeMCU	Microcontroller with Wi-Fi

2.HC-SR04	Ultrasonic distance sensor

3.DHT11	Temperature and Humidity sensor

4.LDR	Light sensor (connected to analog pin A0)

5.Breadboard	For connections

6.Jumper Wires	For wiring components


🔌 Wiring

Sensor	ESP8266 Pin

HC-SR04 TRIG	D1

HC-SR04 ECHO	D2

DHT11 DATA	D3

LDR	A0

📚 Required Libraries
Install these libraries via Arduino IDE → Library Manager:

ESP8266WiFi

Built-in after ESP8266 board setup

ThingSpeak

Library to send data to ThingSpeak

Install via Library Manager or:

Sketch → Include Library → Manage Libraries → Search "ThingSpeak"

DHT Sensor Library

Author: Adafruit

Adafruit Unified Sensor Library



Required dependency for DHT library

⚙️ Arduino IDE Setup for ESP8266

Install ESP8266 Board Support

File → Preferences → Add URL:

http://arduino.esp8266.com/stable/package_esp8266com_index.json

Tools → Board → Board Manager → Install esp8266

Select Board & Port

Tools → Board → NodeMCU 1.0 (ESP-12E Module)

Tools → Port → Select your USB port

🌐 ThingSpeak Setup

Go to https://thingspeak.com

Create an account or log in

Create a New Channel

Field 1: Distance

Field 2: Temperature

Field 3: Humidity

Field 4: Light Level

Save channel

Copy:

Channel ID

Write API Key

Replace these values in your code:

unsigned long channelID = YOUR_CHANNEL_ID;

const char* writeAPIKey = "YOUR_WRITE_API_KEY";



📱 Blynk IoT App

You can also use the Blynk IoT App instead of ThingSpeak.

Steps:

Download Blynk IoT App (Android / iOS)

Create a new template in Blynk Dashboard

Add 4 virtual widgets: V0 (distance), V1 (temp), V2 (humidity), V3 (light)

Copy Auth Token

Use the Blynk.h library and replace ThingSpeak logic with:

Blynk.virtualWrite(V0, distance);

Blynk.virtualWrite(V1, temperature);
...

⚠️ Use Blynk.begin(auth, ssid, pass); instead of manual Wi-Fi connection.


🚀 Uploading Code

Paste the complete code in Arduino IDE

Replace Wi-Fi, ThingSpeak credentials

Select board: NodeMCU 1.0

Select correct COM port

Click ✅ Verify

Click ➡ Upload


🖥️ Accessing Web Interface

Once connected to Wi-Fi, open Serial Monitor (baud 115200)

It will display the IP address (e.g., 192.168.1.8)

Open browser and enter that IP

You’ll see live sensor data in HTML format


🛠️ Use Case

This project is ideal for:

Smart Environment Monitoring (distance for level, temp-humidity for climate, light for brightness)

Garbage Bin Level Detection

Agriculture: Soil light, climate, and distance from water sources

Smart Homes: Automated light adjustment, environmental tracking


📝 Example Output

Serial Monitor:

Connecting to Wi-Fi...

Connected to Wi-Fi!

Distance: 43 cm

Temperature: 25.00 °C

Humidity: 60.00 %

Light Level: 790

Data sent to ThingSpeak successfully!

ThingSpeak: Visit your channel and check the live updating graphs.


📂 Project Directory Structure

ESP8266-IoT-Project/

├── main.ino               # Arduino Sketch

├── README.md              # This file

💡 Tips
Wait 15 seconds between writes to ThingSpeak (free plan limit)

Ensure your Wi-Fi is 2.4GHz, ESP8266 doesn't support 5GHz

Use a resistor voltage divider for LDR if values are off







No file chosenNo file chosen
ChatGPT can make mistakes. Check important info. See Cookie Preferences.
