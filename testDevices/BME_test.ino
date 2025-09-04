#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Create an instance of the BME280 sensor
Adafruit_BME280 bme;

// Time delay for readings (milliseconds)
unsigned long delayTime = 2000; 

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing BME280...");

  // Initialize BME280 sensor
  if (!bme.begin(0x76)) { // Default I2C address is 0x76
    Serial.println("Error: Could not find a valid BME280 sensor. Please check the wiring!");
    while (1); // Stop program if sensor is not found
  }
  
  Serial.println("BME280 sensor initialized successfully.");
  Serial.println("Reading BME280 sensor data...");
  Serial.println();
}

void loop() {
  // Read and print temperature
  float temperature = bme.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Read and print humidity
  float humidity = bme.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Read and print pressure
  float pressure = bme.readPressure() / 100.0F; // Convert to hPa
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  // Add a delay before the next reading
  delay(delayTime);
}
