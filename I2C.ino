#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Wi-Fi credentials
const char* ssid = "ASHURA";
const char* password = "gnam9999";

// ThingSpeak credentials
const char* apiKey = "FXQIUYD5YSJMI70O";
unsigned long channelID = 2794855; // Replace with your ThingSpeak Channel ID

// MQ-135 setup
const int mq135Pin = A0; // Analog pin connected to MQ-135

// ThingSpeak client
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to Wi-Fi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read data from MQ-135 sensor
  int airQualityRaw = analogRead(A0);

  // Print data to Serial Monitor
  Serial.print("MQ-135 Raw Value: ");
  Serial.println(airQualityRaw);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, airQualityRaw); // Use Field 1 for air quality data

  int status = ThingSpeak.writeFields(channelID, apiKey);
  if (status == 200) {
    Serial.println("MQ-135 data sent to ThingSpeak successfully!");
  } else {
    Serial.print("Error sending data to ThingSpeak: ");
    Serial.println(status);
  }

  delay(15000); // ThingSpeak requires a minimum 15-second interval
}
