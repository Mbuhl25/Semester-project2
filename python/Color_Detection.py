import cv2
import numpy as np
import time
import kociemba

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


# check_color funktionen, som tjekker hvilken farve der er på det punkt der bliver tjekket, og returnere en string med den farve der er på det punkt
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
    
    
    
# åbner kameraet og læser et billede, som bruges til at detektere farverne på det billede, og for at finde midtpunktet og de 8 punkter omkring midt
cap = cv2.VideoCapture(0)

ret, frame = cap.read()

# konverterer billedet til HSV format, som bruges til at detektere farverne i check_color funktionen

# finder midtpunktet og de 8 punkter omkring midtpunktet, som bruges til at tjekke farverne på det billede
h, w, _ = frame.shape
midt_x = w // 2  
midt_y = h // 2
afstand = 50

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


# viser de 9 punkter på billedet, som bruges til at tjekke farverne på det billede, og for at se hvor de 9 punkter er på billedet




# get_string funktionen, som tjekker farverne på de 9 punkter, og returnere en string med de farver der er på de 9 punkter
def get_string():
    ret, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
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

# align_cube funktionen, som viser de 9 punkter på en video så man kan sætte op rubikscuben så de 9 punkter er på de rigtige steder
def align_cube():
    while True:
        ret, frame = cap.read()
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

        key = cv2.waitKey(1) & 0xFF

        if key == ord('q'):   # tryk q når kuben er aligned
            break
        

def detect_cube():
    x = ""
    expected = ["Y", "O", "G", "W", "R", "B"]

    for i in range(6):
        while True:
            print("Du skal nu vise side ", expected[i])

            align_cube()
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

#show_points()
#align_cube()
#print(get_string())
print(kociemba.solve(Rename(detect_cube())))