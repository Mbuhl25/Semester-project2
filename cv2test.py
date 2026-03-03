import cv2
import numpy as np

yellow_lower = np.array([15, 50, 20])
yellow_upper = np.array([35, 255, 255])

video = cv2.VideoCapture(0)

print(dir(cv2))

success, img = video.read()
image = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

yellowMask = cv2.inRange(image, yellow_lower, yellow_upper)

cv2.imshow("yellowMask", yellowMask)
cv2.imshow("webcam", img)

cv2.waitKey(1000000)
