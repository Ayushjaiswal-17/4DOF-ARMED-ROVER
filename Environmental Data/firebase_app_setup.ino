#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHT.h"
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// Wi-Fi Credentials
const char* ssid = "Galaxy A52s 5GF184";
const char* password = "12345678";

// Firebase Credentials
#define FIREBASE_HOST "https://esp32-fe54f-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "AIzaSyCY9UV2T4x0VWlmftiv5bqVYxoo8XIvtAk"
// Firebase Configuration
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData firebaseData;
// DHT11 Sensor Configuration
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// MQ135 Gas Sensor
#define MQ135_PIN 34  // Analog pin for MQ135
// Flame Sensor
#define FLAME_SENSOR_PIN 35  // Digital pin for flame sensor
// Impact Sensor (Piezo)
#define PIEZO_SENSOR_PIN 32  // Analog pin for piezo sensor
// Tremor Sensor (Accelerometer or Gyroscope)
#define TREMOR_SENSOR_PIN 33  // Analog pin for tremor sensor
// GPS Module Configuration (Neo-6M)
#define RXD2 16  // GPS RX Pin
#define TXD2 17  // GPS TX Pin
TinyGPSPlus gps;
HardwareSerial gpsSerial(1);
// Function Prototypes
void sendToFirebase(const char* path, float value);
void sendToFirebase(const char* path, String value);
void setup() {
  Serial.begin(115200);
  // Initialize Sensors
  dht.begin();
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(PIEZO_SENSOR_PIN, INPUT);
  pinMode(TREMOR_SENSOR_PIN, INPUT);
  Serial.println("Initializing GPS...");
  gpsSerial.begin(9600, SERIAL_8N1, RXD2, TXD2); // GPS module
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  // Configure Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  if (Firebase.ready()) {
    Serial.println("Connected to Firebase!");
  } else {
    Serial.println("Firebase connection failed!");
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    Serial.printf("Temp: %.2f °C, Humidity: %.2f %%\n", temperature, humidity);
    sendToFirebase("/temperature", temperature);
    sendToFirebase("/humidity", humidity);
  } else {
    Serial.println("Failed to read DHT sensor!");
  }

  // Read MQ135 Gas Sensor
  int gasLevel = analogRead(MQ135_PIN);
  Serial.printf("Gas Level: %d\n", gasLevel);
  sendToFirebase("/gas_level", gasLevel);

  // Read Flame Sensor
  int flameDetected = digitalRead(FLAME_SENSOR_PIN);
  Serial.printf("Flame Detected: %s\n", flameDetected ? "No" : "Yes");
  sendToFirebase("/flame_detected", flameDetected ? "No" : "Yes");

  // Read Impact Sensor (Piezo)
  int impactValue = analogRead(PIEZO_SENSOR_PIN);
  Serial.printf("Impact Value: %d\n", impactValue);
  sendToFirebase("/impact_level", impactValue);

  // Read Tremor Sensor
  int tremorValue = analogRead(TREMOR_SENSOR_PIN);
  Serial.printf("Tremor Level: %d\n", tremorValue);
  sendToFirebase("/tremor_level", tremorValue);

  // Read GPS Data
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    String locationData = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
    Serial.printf("GPS Location: %s\n", locationData.c_str());
    sendToFirebase("/location", locationData);
  } else {
    Serial.println("Waiting for valid GPS data...");
  }

  delay(3000);  // Delay before next reading
}

// Function to send float data to Firebase
void sendToFirebase(const char* path, float value) {
  if (Firebase.setFloat(firebaseData, path, value)) {
    Serial.printf("Sent %s: %.2f\n", path, value);
  } else {
    Serial.printf("Failed to send %s: %s\n", path, firebaseData.errorReason().c_str());
  }
}

// Function to send string data to Firebase
void sendToFirebase(const char* path, String value) {
  if (Firebase.setString(firebaseData, path, value)) {
    Serial.printf("Sent %s: %s\n", path, value.c_str());
  } else {
    Serial.printf("Failed to send %s: %s\n", path, firebaseData.errorReason().c_str());
  }
}