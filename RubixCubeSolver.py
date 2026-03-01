upper = ""
right = ""
front = ""
down = ""
left = ""
back = ""
scrambled = upper + right + front + down + left + back
print(scrambled)

scrambled_new = ""
for i in range(len(scrambled)):
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


import kociemba
print(kociemba.solve(scrambled_new))