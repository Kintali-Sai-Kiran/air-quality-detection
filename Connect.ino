#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
const char* ssid = "ASHURA";
const char* password = "gnam9999";

// Firebase configuration
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Firebase Host and Auth Token
#define FIREBASE_HOST "airquality-28818-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "bbYlrR1mpVx4zcpqhmi6M1IxDrV7YPzeuNIv0AHC"

// Maximum time to wait for Wi-Fi connection (in milliseconds)
const unsigned long wifiTimeout = 30000; // 30 seconds

void setup()
{
  Serial.begin(115200);

  // Connect to Wi-Fi with timeout
  WiFi.begin(ssid, password);
  unsigned long startTime = millis(); // Start time for timeout

  while (WiFi.status() != WL_CONNECTED)
  {
    if (millis() - startTime >= wifiTimeout) // Check if timeout exceeded
    {
      Serial.println("Failed to connect to Wi-Fi within timeout. Terminating...");
      return; // Exit setup if Wi-Fi connection fails
    }
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  Serial.println("Connected to Wi-Fi");

  // Firebase configuration
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialize Firebase
  Firebase.begin(&config, &auth);

  // Test Firebase connection
  if (Firebase.setString(firebaseData, "/Test", "Hello Firebase"))
  {
    Serial.println("Connected to Firebase and test data sent!");
  }
  else
  {
    Serial.print("Failed to connect to Firebase: ");
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
  // Simulated sensor data
  float temperature = 36.9;  // Replace with actual sensor reading
  float humidity = 60.0;     // Replace with actual sensor reading

  // Send temperature data to Firebase
  if (Firebase.setFloat(firebaseData, "/SensorData/Temperature", temperature))
  {
    Serial.println("Temperature data sent successfully!");
  }
  else
  {
    Serial.print("Failed to send temperature data: ");
    Serial.println(firebaseData.errorReason());
  }

  // Send humidity data to Firebase
  if (Firebase.setFloat(firebaseData, "/SensorData/Humidity", humidity))
  {
    Serial.println("Humidity data sent successfully!");
  }
  else
  {
    Serial.print("Failed to send humidity data: ");
    Serial.println(firebaseData.errorReason());
  }

  delay(5000);  // Wait for 5 seconds before the next update
}
