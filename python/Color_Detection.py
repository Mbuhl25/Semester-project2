import cv2
import numpy as np
import time
import kociemba
from collections import Counter

# upper og lower til alle farverne i HSV format, som bruges til at detektere farverne i check_color funktionen
blue_lower = np.array([85, 60, 60])
blue_upper = np.array([130, 255, 255])

green_lower = np.array([35, 50, 50])
green_upper = np.array([85, 255, 255])

yellow_lower = np.array([18, 80, 80])
yellow_upper = np.array([38, 255, 255])

orange_lower = np.array([5, 80, 80])
orange_upper = np.array([17, 255, 255])

white_lower = np.array([0, 0, 140])
white_upper = np.array([179, 80, 255])

pink_lower = np.array([135, 60, 60])
pink_upper = np.array([175, 255, 255])


#checker hvilken farve det er på et punkt
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

def check_color_5_points(hsv, x, y, offset=5):
    colors = [
        check_color(hsv, x, y),             # midten
        check_color(hsv, x - offset, y),    # venstre
        check_color(hsv, x + offset, y),    # højre
        check_color(hsv, x, y - offset),    # op
        check_color(hsv, x, y + offset)     # ned
    ] 
    count = Counter(colors)
    most_common_color, ammount = count.most_common(1)[0]
    
    if ammount >= 3 and most_common_color != "0":
        return most_common_color
    else:
        return "0"
    
    
    
# åbner kameraet og læser et billede, som bruges til at detektere farverne på det billede, og for at finde midtpunktet og de 8 punkter omkring midt
cap = cv2.VideoCapture(1)

ret, frame = cap.read()

h, w, _ = frame.shape
midt_x = w // 2 - 60
midt_y = h // 2 - 30
afstand = 120

top_left_x = midt_x - afstand
top_left_y = midt_y - afstand

midt_left_x = midt_x - afstand
midt_left_y = midt_y

bot_left_x = midt_x - afstand
bot_left_y = midt_y + afstand

top_midt_x = midt_x
top_midt_y = midt_y - afstand

bot_midt_x = midt_x
bot_midt_y = midt_y + afstand

top_rigtht_x = midt_x + afstand
top_rigtht_y = midt_y - afstand

midt_right_x = midt_x + afstand
midt_right_y = midt_y

bot_right_x = midt_x + afstand
bot_right_y = midt_y + afstand

punkter = [
    (top_left_x, top_left_y),
    (top_midt_x, top_midt_y),
    (top_rigtht_x, top_rigtht_y),
    (midt_left_x, midt_left_y),
    (midt_x, midt_y),
    (midt_right_x, midt_right_y),
    (bot_left_x, bot_left_y),
    (bot_midt_x, bot_midt_y),
    (bot_right_x, bot_right_y)
    ]

# get_string funktionen, som tjekker farverne på de 9 punkter, og returnere en string med de farver der er på de 9 punkter
def get_string():
    ret, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    x = ""
    for px, py in punkter:
        x += check_color_5_points(hsv, px, py)
    return x

# align_cube funktionen, som viser de 9 punkter på en video så man kan sætte op rubikscuben så de 9 punkter er på de rigtige steder
def align_cube():
    while True:
        ret, frame = cap.read()
        for px, py in punkter:
            cv2.circle(frame, (px, py), 3, (0, 255, 0), -1)

        cv2.imshow("camera", frame)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):   
            break
        
def align_cube_timer():
    start = time.time()
    delay = 5
    while True:
        ret, frame = cap.read()
        for px, py in punkter:
            cv2.circle(frame, (px, py), 3, (0, 255, 0), -1)

        cv2.imshow("camera", frame)
        cv2.waitKey(10)
        if time.time() - start > delay:
            break
        

def detect_cube_loop():
    x = ""
    expected = ["Y", "O", "G", "W", "R", "B"]
    for i in range(6):
        while True:
            print("Du skal nu vise side ", expected[i])

            align_cube_timer()
            string = get_string()
            print(string)
            if string[4] != expected[i]:
                print(f"forkert farve på midtpunktet, forventet {expected[i]}, fundet {string[4]}")
                time.sleep(1)
                continue
            if "0" in string:
                    print("der er en eller flere farver der ikke kunne detekteres, prøv igen")
                    time.sleep(1)
                    continue
            else:    
                print("korrekt side")
                x += string
                print("Dette er den nuværende string: ", string)
                print("Dette er den samlede string: ", x)

                break
    return x
    
def detect_cube_Once(farve):
    x = ""
    while True:
        print("Du skal nu vise side ", farve)

        align_cube()
        string = get_string()
        print(string)
        if string[4] != farve:
            print(f"forkert farve på midtpunktet, forventet {farve}, fundet {string[4]}")
            time.sleep(1)
            continue
        if "0" in string:
                print("der er en eller flere farver der ikke kunne detekteres, prøv igen")
                time.sleep(1)
                continue
        else:    
            print("korrekt side")
            print("Dette er den nye string: ", string)

            break
    return string

def Rename(x):
    scrambled = x
    scrambled_new = ""
    for i in range(len(x)):
        if scrambled[i] == "R":
            scrambled_new += "L"

        elif scrambled[i] == "O":
            scrambled_new += "R"

        elif scrambled[i] == "Y":
            scrambled_new += "U"

        elif scrambled[i] == "G":
            scrambled_new += "F"

        elif scrambled[i] == "W":
            scrambled_new += "D"

        elif scrambled[i] == "B":
            scrambled_new += "B"

    print(scrambled_new)
    totalU = 0
    totalR = 0
    totalF = 0
    totalD = 0
    totalL = 0
    totalB = 0
    for letter in scrambled_new:
        if letter == "U":
            totalU += 1
        if letter == "R":
            totalR += 1
        if letter == "F":
            totalF += 1
        if letter == "D":
            totalD += 1
        if letter == "L":
            totalL += 1
        if letter == "B":
            totalB += 1
    print("total U = ", totalU)
    print("total R = ", totalR)
    print("total F = ", totalF)
    print("total D = ", totalD)
    print("total L = ", totalL)
    print("total B = ", totalB)
    return scrambled_new


print(kociemba.solve(Rename(detect_cube_loop())))
#align_cube()
