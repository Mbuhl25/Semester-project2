# Første gang
sørg for at git er installeret:
```
git -v
```
Skulle gerne outputte:
```
git version 2.xx.x
```

Find den folder, hvor du vil have semesterprojektet til at ligge. F.eks:
```
~/Desktop/SCHOOL/2_semester
```
højreklik i stifinderen og tryk på: "Open in terminal"

i terminalen skriv:
```
git clone <Tryk på den grønne knap i toppen af git og kopier linket>
```
Tillykke dygtige dreng. Nu har du et repository.

# Git Workflow
*Alt dette fungere kun når du er i den rigtige mappe på command line*
Inden du begynder på din opgave, så kan du lige skrive
```
git pull
```

Så laver du en *feature branch*, til den specifikke opgave du skal lave
```
git checkout -b Feature/<NameOfFeature>
eksempel: git checkout -b Feature/ComputerToRobotCommunication
```

Nu kan du tilføje filer til mappen, redigere filer, slette filer ligeså meget du vil.
Når du er tilfreds med dine ændringer kan du skrive
```
git status
```
For at se hvad du har ændret.

så tilføjer du dine filer til staging med
```
git add <fil_1> <fil_2> ... <fil_n> 

git add . # tilføjer alle ændringer til staging
```
derefter skal du commit. Det er ligesom et checkpoint.
```
git commit
```
Så kommer du ind i din text editor, og der skriver du en commit besked.

# Other
## libraries to look at
[cv2 library](https://pypi.org/project/opencv-python/)

[kociembra (løs rubiks terninger)](https://pypi.org/project/kociemba/)

## Cool video
[cv2 color detection with webcam](https://www.youtube.com/watch?v=cMJwqxskyek)
