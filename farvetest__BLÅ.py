import cv2
import numpy as np

# HSV range for blue
lower = np.array([100, 150, 50])
upper = np.array([130, 255, 255])

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower, upper)

    h, w, _ = frame.shape
    x = w // 2
    y = h // 2

    if mask[y, x] == 255:
        print("Blue detected at center")
    else:
        print("No blue detected at center")

    cv2.circle(frame, (x, y), 5, (0, 0, 255), -1)
    cv2.imshow("camera", frame)

    if cv2.waitKey(1) == 27:  # ESC to exit
        break

cap.release()
cv2.destroyAllWindows()