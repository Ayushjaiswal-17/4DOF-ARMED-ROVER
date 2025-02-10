import cv2
import mediapipe as mp
import math
import serial  # For communication with ESP32

# Configure Serial Communication (adjust COM port and baud rate)
ESP32_PORT = 'COM13'  # Replace with your ESP32 COM port (e.g., 'COM3', '/dev/ttyUSB0')
BAUD_RATE = 9600
esp32 = serial.Serial(ESP32_PORT, BAUD_RATE)

# Mediapipe Hand Detection
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(static_image_mode=False, max_num_hands=1, min_detection_confidence=0.7)
mp_draw = mp.solutions.drawing_utils

def calculate_distance(pt1, pt2):
    """Calculate the Euclidean distance between two points."""
    return math.sqrt((pt1[0] - pt2[0])*2 + (pt1[1] - pt2[1])*2)

def map_value(value, in_min, in_max, out_min, out_max):
    """Map a value from one range to another."""
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# Open Webcam
cap = cv2.VideoCapture(0)

print("Starting webcam... Press 'q' to exit.")

try:
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            print("Failed to grab frame. Exiting...")
            break

        # Convert frame to RGB
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = hands.process(frame_rgb)

        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                # Draw hand landmarks
                mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

                # Get thumb tip (landmark 4) and index finger tip (landmark 8) positions
                thumb_tip = hand_landmarks.landmark[4]
                index_tip = hand_landmarks.landmark[8]

                # Convert to pixel coordinates
                thumb_coords = (int(thumb_tip.x * frame.shape[1]), int(thumb_tip.y * frame.shape[0]))
                index_coords = (int(index_tip.x * frame.shape[1]), int(index_tip.y * frame.shape[0]))

                # Draw points on the frame
                cv2.circle(frame, thumb_coords, 10, (255, 0, 0), -1)
                cv2.circle(frame, index_coords, 10, (0, 255, 0), -1)

                # Calculate distance between thumb and index finger
                distance = calculate_distance(thumb_coords, index_coords)

                # Map the distance to a servo angle (0–180 degrees)
                angle = int(map_value(distance, 30, 200, 0, 180))
                angle = max(0, min(180, angle))  # Clamp the angle between 0 and 180

                # Send the angle to ESP32
                esp32.write(f"{angle}\n".encode())

                # Display the distance and angle on the frame
                cv2.putText(frame, f"Distance: {int(distance)} px", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
                cv2.putText(frame, f"Angle: {angle} deg", (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)

        # Show the frame
        cv2.imshow("Finger Distance to Servo Angle", frame)

        # Exit on 'q' key
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

except Exception as e:
    print(f"An error occurred: {e}")

finally:
    cap.release()
    cv2.destroyAllWindows()
    esp32.close()
    print("Program terminated.")
