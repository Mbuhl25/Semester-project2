import cv2
import numpy as np
import time

blue_lower = np.array([85, 40, 40])
blue_upper = np.array([125, 255, 255])

green_lower = np.array([30, 40, 40])
green_upper = np.array([90, 255, 255])

yellow_lower = np.array([15, 30, 30])
yellow_upper = np.array([40, 255, 255])

white_lower = np.array([0, 0, 160])
white_upper = np.array([179, 80, 255])

orange_lower = np.array([5, 40, 40])
orange_upper = np.array([25, 255, 255])

pink_lower = np.array([125, 40, 40])
pink_upper = np.array([179, 255, 255])

def check_color(hsv, x, y):    
    if cv2.inRange(hsv, blue_lower, blue_upper)[y, x] == 255:
        punkt = "B"
        return punkt
    elif cv2.inRange(hsv, green_lower, green_upper)[y, x] == 255:
        punkt = "G"
        return punkt
    elif cv2.inRange(hsv, yellow_lower, yellow_upper)[y, x] == 255:
        punkt = "Y"
        return punkt
    elif cv2.inRange(hsv, white_lower, white_upper)[y, x] == 255:
        punkt = "W"
        return punkt
    elif cv2.inRange(hsv, orange_lower, orange_upper)[y, x] == 255:
        punkt = "O"
        return punkt
    elif cv2.inRange(hsv, pink_lower, pink_upper)[y, x] == 255:
        punkt = "R"
        return punkt
    else:
        return str("0")  
    



cap = cv2.VideoCapture(0)
ret, frame = cap.read()


hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

h, w, _ = frame.shape
midt_x = w // 2  
midt_y = h // 2

top_left_x = midt_x - 30
top_left_y = midt_y - 30

midt_left_x = midt_x - 30
midt_left_y = midt_y

bot_left_x = midt_x - 30
bot_left_y = midt_y + 30

top_midt_x = midt_x
top_midt_y = midt_y - 30

bot_midt_x = midt_x
bot_midt_y = midt_y + 30

top_rigtht_x = midt_x + 30
top_rigtht_y = midt_y - 30

midt_right_x = midt_x + 30
midt_right_y = midt_y

bot_right_x = midt_x + 30
bot_right_y = midt_y + 30



def show_points():
    # midtpunktet:
    cv2.circle(frame, (midt_x, midt_y), 3, (0, 0, 255), -1)
    # Top left punktet:
    cv2.circle(frame, (top_left_x, top_left_y), 3, (0, 255, 0), -1)
    # Midt left punktet:
    cv2.circle(frame, (midt_left_x, midt_left_y), 3, (255, 0, 0), -1)
    # Bot left punktet:
    cv2.circle(frame, (bot_left_x, bot_left_y), 3, (0, 255, 255), -1)
    # Top midt punktet:
    cv2.circle(frame, (top_midt_x, top_midt_y), 3, (255, 255, 0), -1)
    # Bot midt punktet:
    cv2.circle(frame, (bot_midt_x, bot_midt_y), 3, (255, 0, 255), -1)
    # Top right punktet:
    cv2.circle(frame, (top_rigtht_x, top_rigtht_y), 3, (255, 0, 0), -1)
    # Midt right punktet:
    cv2.circle(frame, (midt_right_x, midt_right_y), 3, (0, 255, 0), -1)
    # Bot right punktet:
    cv2.circle(frame, (bot_right_x, bot_right_y), 3, (0, 0, 255), -1)

    cv2.imshow("camera", frame)
    cv2.waitKey(0)
    cap.release()
    cv2.destroyAllWindows()




def get_string():
    x = ""
    for i in range(9): 
        if i == 0:
            x += check_color(hsv, top_left_x, top_left_y)
        elif i == 1:
            x += check_color(hsv, top_midt_x, top_midt_y)
        elif i == 2:
            x += check_color(hsv, top_rigtht_x, top_rigtht_y)
        elif i == 3:
            x += check_color(hsv, midt_left_x, midt_left_y)
        elif i == 4:
            x += check_color(hsv, midt_x, midt_y)
        elif i == 5:
            x += check_color(hsv, midt_right_x, midt_right_y)
        elif i == 6:
            x += check_color(hsv, bot_left_x, bot_left_y)
        elif i == 7:
            x += check_color(hsv, bot_midt_x, bot_midt_y)
        elif i == 8:
            x += check_color(hsv, bot_right_x, bot_right_y)
    return x


print(get_string())
show_points()