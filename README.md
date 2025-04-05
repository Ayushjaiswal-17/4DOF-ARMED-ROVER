# 4-DOF Armed Rover

## Overview
The **4-DOF Armed Rover** is a versatile, IoT-enabled rover designed for rescue missions and disaster relief. It features a four-degree-of-freedom (4-DOF) robotic arm mounted on a mobile rover, capable of autonomous and manual operation. The system is controlled via Firebase and Blynk, enabling real-time data transmission and remote operation.
![WhatsApp Image 2025-03-31 at 12 00 15_a0666d68](https://github.com/user-attachments/assets/b50bb74c-3904-46c7-b317-88b452671d41)
## Features
- **4-DOF Robotic Arm** for object manipulation
- **Rover Mobility** with 4 independent motors
- **Real-time Data Streaming** to Website via Firebase
- **Rescue and Disaster Relief Applications**
- **ESP32-based Communication** with integrated sensors

## Hardware Components
- **Microcontrollers**: ESP32 (x2) for rover and arm control
- **Motors**: 4 DC motors for rover movement, 4 servo motors for arm
- **Power Supply**: Li-Po battery pack
- **Additional Sensors**: Ultrasonic, IR, Tremor, Gas, DHT11, flame etc

## Software & Technologies Used
- **Arduino IDE** for programming ESP32
- **Firebase** for cloud-based control
- **Blynk IoT** for mobile-based manual control
- **Python** for open cv
- **http** communication protocol for controlling the rover

## Installation & Setup
### 1. Install Required Libraries
Ensure you have the following libraries installed in Arduino IDE:
- `WiFi.h`
- `FirebaseESP8266.h`
- `Servo.h`
- `BlynkSimpleEsp8266.h`

### 2. Flash the Code
- Open the Arduino IDE.
- Select the correct **Board** (ESP32/ESP8266) and **COM Port**.
- Upload the firmware to both the **rover ESP32** and **arm ESP32**.

### 3. Configure Firebase
- Create a Firebase project.
- Obtain the **Database URL** and **API Key**.
- Update the credentials in the code.

### 4. Set Up Blynk
- Install the **Blynk IoT** app on your phone.
- Create a new project and obtain an **Authentication Token**.
- Update the credentials in the code.

  
![WhatsApp Image 2025-04-03 at 21 01 15_46401ea3](https://github.com/user-attachments/assets/59f39ab7-db11-4206-8c82-76615475d243)

![WhatsApp Image 2025-03-31 at 12 00 17_5fb3efab](https://github.com/user-attachments/assets/dafc6e43-caf0-4992-a593-c808e7e5ab61)




## Future Enhancements
- Implement **autonomous navigation** using LiDAR/vision sensors.
- Improve **AI-based object recognition** for more precise rescue operations.
- Add **haptic feedback** for better control experience.

## Contributors
- [Saunok Roy](https://github.com/sp4m-08)  
- [Hrithika](https://github.com/rith26)  
- [Shravan](https://github.com/Shravan652)


## Contact
For any queries or collaboration, reach out via:
- **Email**:  ayushjaiswal31657@gmail.com
- **LinkedIn**: http://www.linkedin.com/in/ayush-jaiswal007
- **GitHub**: https://github.com/Ayushjaiswal-17

---
##                                                                                       Made with ❤ by ISTE VIT


