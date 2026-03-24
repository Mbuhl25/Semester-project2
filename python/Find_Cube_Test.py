import cv2
import numpy as np

def find_rubiks_cube(frame):
    h, w, _ = frame.shape

    # 🔹 ROI (midten)
    roi = frame[h//4:3*h//4, w//4:3*w//4]

    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)

    # 🔹 Farvemasker
    masks = []
    masks.append(cv2.inRange(hsv, (15,80,80), (40,255,255)))   # gul
    masks.append(cv2.inRange(hsv, (90,80,80), (140,255,255))) # blå
    masks.append(cv2.inRange(hsv, (135,60,60), (175,255,255))) # pink
    masks.append(cv2.inRange(hsv, (35,80,80), (90,255,255)))   # grøn
    masks.append(cv2.inRange(hsv, (0,0,180), (180,80,255)))    # hvid
    masks.append(cv2.inRange(hsv, (10,100,100), (25,255,255))) # orange

    # 🔹 Kombiner masker
    mask = masks[0]
    for m in masks[1:]:
        mask = cv2.bitwise_or(mask, m)

    # 🔥 VIGTIGT: saml kuben til én blob
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (15,15))
    mask = cv2.dilate(mask, kernel, iterations=2)
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

    # 🔹 Find konturer
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if not contours:
        return frame, None

    # 🔹 Største kontur
    largest = max(contours, key=cv2.contourArea)

    if cv2.contourArea(largest) < 8000:
        return frame, None

    # 🔥 Brug convex hull (mere stabil form)
    hull = cv2.convexHull(largest)

    x, y, w_box, h_box = cv2.boundingRect(hull)

    # 🔹 Flyt fra ROI til original frame
    x += w//4
    y += h//4

    # 🔹 Tegn firkant
    cv2.rectangle(frame, (x,y), (x+w_box, y+h_box), (0,255,0), 3)

    return frame, (x, y, w_box, h_box)


# 🔹 MAIN PROGRAM
cap = cv2.VideoCapture(1)  # prøv 0 hvis 1 ikke virker

while True:
    ret, frame = cap.read()

    if not ret:
        print("Kamera virker ikke")
        break

    frame, cube = find_rubiks_cube(frame)

    if cube is not None:
        cv2.putText(frame, "Cube detected!", (50,50),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2)

    cv2.imshow("Cube Detection", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()