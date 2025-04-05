#include <ESP8266WiFi.h>
#include <Servo.h>
  
// Create Servo objects
Servo servo1, servo2, servo3;

// Define pins for the servos
const int servoPin1 = D4;
const int servoPin2 = D5;
const int servoPin3 = D6;

void setup() {
    // Start Serial Monitor
    Serial.begin(115200);
    
    // Attach the servos to the pins
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
    
    Serial.println("Enter servo number (1-3) and angle (0-180) in format: servo,angle");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n'); // Read input from Serial Monitor
        input.trim(); // Remove any whitespace or newline characters

        int commaIndex = input.indexOf(',');
        if (commaIndex != -1) {
            String servoNumberStr = input.substring(0, commaIndex);
            String angleValueStr = input.substring(commaIndex + 1);
            
            int servoNumber = servoNumberStr.toInt();
            int angle = angleValueStr.toInt();
            
            if (servoNumber >= 1 && servoNumber <= 3 && angle >= 0 && angle <= 180) {
                // Set the appropriate servo
                if (servoNumber == 1) servo1.write(angle);
                else if (servoNumber == 2) servo2.write(angle);
                else if (servoNumber == 3) servo3.write(angle);
                
                Serial.print("Servo ");
                Serial.print(servoNumber);
                Serial.print(" Angle Set to: ");
                Serial.println(angle);
            } else {
                Serial.println("Invalid input. Enter in format: servo,angle (e.g., 1,90)");
            }
        } else {
            Serial.println("Invalid format. Use: servo,angle (e.g., 1,90)");
        }
    }
}

