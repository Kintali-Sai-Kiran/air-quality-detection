#include <ESP8266WiFi.h>        // for wi-fi connection
#include <ThingSpeak.h>         // To send data to Thingspeak
#include <Wire.h>               // For I2C Communication (BME280)
#include <Adafruit_Sensor.h>    // sensor libraries for BME280
#include <Adafruit_BME280.h>

const char* ssid = "ASHURA";        // wi-fi Id
const char* password = "gnam9999";  // Wi-fi password

unsigned long myChannelNumber = 2794855;          // Thingspeak Private chanel Id
const char* myWriteAPIKey = "FCFGXXTKNO4ERKDF";   // Thingspeak write API

int mq135Pin = A0;      // Analog pin for MQ-135

Adafruit_BME280 bme;    // Object for BME280

WiFiClient client;      // Object for Wi-fi communication

void setup()  // for Serial Communication
{
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());

  if (!bme.begin(0x76))     // Stops the execution
  {
    Serial.println("Could not find BME280 sensor! Check wiring.");
    while (1);
  }
  Serial.println("BME280 sensor initialized successfully.");

  ThingSpeak.begin(client);   // Initialize communication with Thingspeak
}

void loop()
{
  int rawValue = analogRead(mq135Pin);  // Take Analog value from MQ-135 (pin = A0)
  float ppm = rawToPPM(rawValue);       // Converting Raw value to ppm

  float temperature = bme.readTemperature();    // Temperature in °C
  float humidity = bme.readHumidity();          // Humidity in %
  float pressure = bme.readPressure() / 100.0F; // Pressure in hPa

  Serial.print("MQ-135 Raw Value: ");
  Serial.println(rawValue);
  Serial.print("MQ-135 Calculated PPM: ");
  Serial.println(ppm);
  Serial.print("BME280 Temperature (°C): ");
  Serial.println(temperature);
  Serial.print("BME280 Humidity (%): ");
  Serial.println(humidity);
  Serial.print("BME280 Pressure (hPa): ");
  Serial.println(pressure);
  Serial.println("\n\n");
  

  ThingSpeak.setField(1, rawValue);    // MQ-135 Raw Value
  ThingSpeak.setField(2, ppm);         // MQ-135 PPM Value
  ThingSpeak.setField(3, temperature); // Temperature from BME280
  ThingSpeak.setField(4, humidity);    // Humidity from BME280
  ThingSpeak.setField(5, pressure);    // Pressure from BME280
  int responseCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);    // 
  
  
  if (responseCode == 200)      // Display whether the data is sent to Thingspeak or not
  {
    Serial.println("Data successfully sent to ThingSpeak.");
  }
  else
  {
    Serial.print("Error sending data. Response code: ");
    Serial.println(responseCode);
  }

  delay(15000); // Delay of 15 seconds
}

float rawToPPM(int rawValue)    // Data Convertion from Raw to ppm
{
  float ppm = (rawValue / 1023.0) * 1000.0;
  return ppm;
}
