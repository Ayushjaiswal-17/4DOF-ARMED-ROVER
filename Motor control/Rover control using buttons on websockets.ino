#include <WiFi.h>
#include <WebServer.h>

// WiFi Credentials
const char* ssid = "Galaxy A52s 5GF184";
const char* password = "12345678";

WebServer server(80);

// Motor Driver Pins
#define MOTOR1_IN1 26
#define MOTOR1_IN2 27
#define MOTOR2_IN3 14
#define MOTOR2_IN4 12

// Ultrasonic Sensor Pins
#define TRIG 5
#define ECHO 18

bool autonomousMode = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR2_IN3, OUTPUT);
  pinMode(MOTOR2_IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_GET, moveForward);
  server.on("/backward", HTTP_GET, moveBackward);
  server.on("/left", HTTP_GET, turnLeft);
  server.on("/right", HTTP_GET, turnRight);
  server.on("/stop", HTTP_GET, stopMotors);
  server.on("/toggleAuto", HTTP_GET, toggleAutonomous);

  server.begin();
}

void loop() {
  server.handleClient();
  if (autonomousMode) {
    float distance = getDistance();
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance > 20) {
      moveForward();
    } else {
      stopMotors();
      delay(500);
      turnLeft();
      delay(700);
    }
  }
}

void handleRoot() {
  server.send(200, "text/html", "<html><style>body{display:center}</style><body><h1>ESP32 Web Control</h1><button onclick=\"location.href='/forward'\">Forward</button><button onclick=\"location.href='/backward'\">Backward</button><button onclick=\"location.href='/left'\">Left</button><button onclick=\"location.href='/right'\">Right</button><button onclick=\"location.href='/stop'\">Stop</button><button onclick=\"location.href='/toggleAuto'\">Toggle Auto</button></body></html>");
}

void toggleAutonomous() {
  autonomousMode = !autonomousMode;
  server.send(200, "text/plain", autonomousMode ? "Autonomous Mode Enabled" : "Manual Mode Enabled");
  if (!autonomousMode) stopMotors();
}

void moveForward() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  digitalWrite(MOTOR2_IN3, HIGH);
  digitalWrite(MOTOR2_IN4, LOW);
  server.send(200, "text/plain", "Moving Forward");
}

void moveBackward() {
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN3, LOW);
  digitalWrite(MOTOR2_IN4, HIGH);
  server.send(200, "text/plain", "Moving Backward");
}

void turnLeft() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  digitalWrite(MOTOR2_IN3, LOW);
  digitalWrite(MOTOR2_IN4, HIGH);
  server.send(200, "text/plain", "Turning Left");
}

void turnRight() {
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN3, HIGH);
  digitalWrite(MOTOR2_IN4, LOW);
  server.send(200, "text/plain", "Turning Right");
}

void stopMotors() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN3, LOW);
  digitalWrite(MOTOR2_IN4, LOW);
  server.send(200, "text/plain", "Motors Stopped");
}

float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH);
  return duration * 0.034 / 2;
