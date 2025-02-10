#include <WiFi.h>
#include <ESP32Servo.h> // Include ESP32Servo library

Servo servo1;             // Create servo object for the first servo
Servo servo2;             // Create servo object for the second servo
Servo servo3;  
Servo servo4;  
const int ServoPin1 = 13;  // GPIO pin for the first servo
const int ServoPin2 = 14;  // GPIO pin for the second servo
const int ServoPin3 = 15;  // GPIO pin for the third servo
const int ServoPin4 = 16;  // GPIO pin for the third servo

int servoAngle1 = 90;      // Initial angle of the first servo (90°)
int servoAngle2 = 90;      // Initial angle of the second servo (90°)
int servoAngle3 = 90;      // Initial angle of the second servo (90°)
int servoAngle4 = 90;      // Initial angle of the second servo (90°)

const char* ssid = "Galaxy A52s 5GF184";       // Your Wi-Fi SSID
const char* password = "12345678"; // Your Wi-Fi password

WiFiServer server(80);      // Create a web server on port 80

void setup() {
  Serial.begin(115200);     
  servo1.attach(ServoPin1);  // Attach the first servo to the pin
  servo2.attach(ServoPin2);  // Attach the second servo to the pin
  servo3.attach(ServoPin3);  // Attach the second servo to the pin
  servo4.attach(ServoPin4);  // Attach the second servo to the pin
  servo1.write(servoAngle1); // Set initial position for the first servo
  servo2.write(servoAngle2); // Set initial position for the second servo
  servo3.write(servoAngle3); // Set initial position for the second servo
  servo4.write(servoAngle4); // Set initial position for the second servo

  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Parse the request for servo1 angle
    if (request.indexOf("GET /servo1?angle=") >= 0) {
      int angleIndex = request.indexOf("angle=") + 6;
      int ampersandIndex = request.indexOf('&', angleIndex);
      String angleStr = request.substring(angleIndex, ampersandIndex);
      servoAngle1 = angleStr.toInt();
      if (servoAngle1 >= 0 && servoAngle1 <= 180) {
        servo1.write(servoAngle1); // Move the first servo to the requested angle
        Serial.print("Servo1 angle set to: ");
        Serial.println(servoAngle1);
      }
    }

    // Parse the request for servo2 angle
    if (request.indexOf("GET /servo2?angle=") >= 0) {
      int angleIndex = request.indexOf("angle=") + 6;
      int ampersandIndex = request.indexOf('&', angleIndex);
      String angleStr = request.substring(angleIndex, ampersandIndex);
      servoAngle2 = angleStr.toInt();
      if (servoAngle2 >= 0 && servoAngle2 <= 180) {
        servo2.write(servoAngle2); // Move the second servo to the requested angle
        Serial.print("Servo2 angle set to: ");
        Serial.println(servoAngle2);
      }
    }

     // Parse the request for servo3 angle
    if (request.indexOf("GET /servo3?angle=") >= 0) {
      int angleIndex = request.indexOf("angle=") + 6;
      int ampersandIndex = request.indexOf('&', angleIndex);
      String angleStr = request.substring(angleIndex, ampersandIndex);
      servoAngle3 = angleStr.toInt();
      if (servoAngle3 >= 0 && servoAngle3 <= 180) {
        servo1.write(servoAngle3); // Move the first servo to the requested angle
        Serial.print("Servo3 angle set to: ");
        Serial.println(servoAngle3);
      }
    }
     // Parse the request for servo4 angle
    if (request.indexOf("GET /servo4?angle=") >= 0) {
      int angleIndex = request.indexOf("angle=") + 6;
      int ampersandIndex = request.indexOf('&', angleIndex);
      String angleStr = request.substring(angleIndex, ampersandIndex);
      servoAngle4 = angleStr.toInt();
      if (servoAngle4 >= 0 && servoAngle4 <= 180) {
        servo1.write(servoAngle4); // Move the first servo to the requested angle
        Serial.print("Servo4 angle set to: ");
        Serial.println(servoAngle4);
      }
    }

    // Send HTML response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head><title>Dual Servo Control</title></head>");
    client.println("<body><h1>ESP32 Servo Control</h1>");

    // Slider for Servo1
    client.println("<p>Servo 1:</p>");
    client.println("<input type=\"range\" min=\"0\" max=\"180\" value=\"" + String(servoAngle1) + "\" onchange=\"setServo1Angle(this.value)\">");
    client.println("<p>Current Angle: " + String(servoAngle1) + "°</p>");

    // Slider for Servo2
    client.println("<p>Servo 2:</p>");
    client.println("<input type=\"range\" min=\"0\" max=\"180\" value=\"" + String(servoAngle2) + "\" onchange=\"setServo2Angle(this.value)\">");
    client.println("<p>Current Angle: " + String(servoAngle2) + "°</p>");
    // Slider for Servo3
    client.println("<p>Servo 3:</p>");
    client.println("<input type=\"range\" min=\"0\" max=\"180\" value=\"" + String(servoAngle3) + "\" onchange=\"setServo3Angle(this.value)\">");
    client.println("<p>Current Angle: " + String(servoAngle3) + "°</p>");
    // Slider for Servo4
    client.println("<p>Servo 4:</p>");
    client.println("<input type=\"range\" min=\"0\" max=\"180\" value=\"" + String(servoAngle4) + "\" onchange=\"setServo4Angle(this.value)\">");
    client.println("<p>Current Angle: " + String(servoAngle4) + "°</p>");

    // JavaScript for handling slider updates
    client.println("<script>");
    client.println("function setServo1Angle(angle) {");
    client.println("  var xhttp = new XMLHttpRequest();");
    client.println("  xhttp.open(\"GET\", \"/servo1?angle=\" + angle + \"&\", true);");
    client.println("  xhttp.send();");
    client.println("}");

    client.println("function setServo2Angle(angle) {");
    client.println("  var xhttp = new XMLHttpRequest();");
    client.println("  xhttp.open(\"GET\", \"/servo2?angle=\" + angle + \"&\", true);");
    client.println("  xhttp.send();");
    client.println("}");

    client.println("function setServo3Angle(angle) {");
    client.println("  var xhttp = new XMLHttpRequest();");
    client.println("  xhttp.open(\"GET\", \"/servo1?angle=\" + angle + \"&\", true);");
    client.println("  xhttp.send();");
    client.println("}");

    client.println("function setServo4Angle(angle) {");
    client.println("  var xhttp = new XMLHttpRequest();");
    client.println("  xhttp.open(\"GET\", \"/servo1?angle=\" + angle + \"&\", true);");
    client.println("  xhttp.send();");
    client.println("}");

    client.println("</script>");

    client.println("</body></html>");
    client.stop();
  }
}
