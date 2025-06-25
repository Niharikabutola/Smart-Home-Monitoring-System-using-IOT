#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

// Wi-Fi credentials
const char* ssid = "Netplus_First_Floor";
const char* password ="Google@31";

// ThingSpeak credentials
unsigned long channelID = 2797530; 
const char* writeAPIKey = "PACJ3HM7ZPU4TLIE";

// Pin Definitions
#define TRIG_PIN D1
#define ECHO_PIN D2
#define DHT_PIN D3
#define DHT_TYPE DHT11

// Variables
DHT dht(DHT_PIN, DHT_TYPE);
WiFiClient client;
long duration;
int distance;
float temperature;
float humidity;
int lightLevel;

void setup() {
  Serial.begin(115200);
  
  // Initialize Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin("Netplus_First_Floor","Google@31");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);
  
  // Initialize DHT sensor
  dht.begin();

  // Configure pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Measure distance using HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;  // Distance in cm

  // Measure temperature and humidity
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Measure light level using LDR
  lightLevel = analogRead(A0);

  // Log data to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, distance);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, humidity);
  ThingSpeak.setField(4, lightLevel);

  long response = ThingSpeak.writeFields( 2797530, "PACJ3HM7ZPU4TLIE");
  if (response == 200) {
    Serial.println("Data sent to ThingSpeak successfully!");
  } else {
    Serial.println("Failed to send data to ThingSpeak.");
  }

  // Serve data over Web Interface
  serveWebInterface();

  delay(15000);  // Wait 15 seconds before the next reading
}

void serveWebInterface() {
  WiFiClient client = Server.available();
  if (client) {
    Serial.println("New Client Connected");
    String response = "<html><body>";
    response += "<h1>Sensor Data</h1>";
    response += "<p>Distance: " + String(distance) + " cm</p>";
    response += "<p>Temperature: " + String(temperature) + " °C</p>";
    response += "<p>Humidity: " + String(humidity) + " %</p>";
    response += "<p>Light Level: " + String(lightLevel) + "</p>";
    response += "</body></html>";
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print(response);
    client.stop();
    Serial.println("Client Disconnected");
  }
}
