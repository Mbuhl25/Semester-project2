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
## Lav ændringer
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

* i Nano: skriv din commit besked efterfulgt af ctl+s, ctl+x
* i vim: tryk "i", skriv din commit besked, efterfulgt af esc, "wq!" enter.

Nu har du lavet et commit. Dem kan du lave så mange af, som du har brug for

## Pushing
Når du er tilfreds med dine ændringer skal du pushe. Det gør du på denne måde.
```
git push origin HEAD:<Navn_på_din_feature>
```
Alle fejl der kommer her spørger du bare chat om. Det kan gå galt på mange måder når ens branch er foran eller bagved eller ved siden af eller hvad ved jeg?!?!

Hvis det virker og printer noget alla:
```
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 28 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 934 bytes | 934.00 KiB/s, done.
Total 4 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
remote: 
remote: Create a pull request for 'Feature/Readme' on GitHub by visiting:
remote:      https://github.com/Mbuhl25/Semester-project2/pull/new/Feature/Readme
remote: 
To https://github.com/Mbuhl25/Semester-project2.git
 * [new branch]      HEAD -> Feature/<Navn_pa_dit_repo>
```

Så kan du gå ind på github.com og enten:
* er der en gul boks i toppen af det hele, hvor du kan trykke "*Open pull request*"
* ellers kan du trykke på "branches" til højre for drop-down menuen, hvorefter du vælger din branch. Inde på den branch er en boks "**This branch is 1 commit ahead of and 3 commits behind main.**", der trykker du contribute, og "*Open pull request*"

Så følger du bare de grønne knapper. "*Create pull request*" og derefter "*Merge pull request*".



# Other
## libraries to look at
[cv2 library](https://pypi.org/project/opencv-python/)

[kociembra (løs rubiks terninger)](https://pypi.org/project/kociemba/)

## Cool video
[cv2 color detection with webcam](https://www.youtube.com/watch?v=cMJwqxskyek)
