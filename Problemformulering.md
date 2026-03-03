Målet er at løse en rubiksterning.

Hvordan?

Vi vil kommunikere med en UR5 robot ved hjælp af kommandoer i c++. Med denne funktionalitet vil vi kunne rykke rundt på rubiks terningen og placerer den i positioner så man kan dreje alle 6 sider med eller mod uret.
Måden vi drejer på er ved hjælp af en hjemmelavet gripper, der består af en servo motor, der kan åbne og lukke også ved hjælp af c++.
Vi benytter importerede python biblioteker til at bestemme algoritmen hvorved terningen skal løses. biblioteket kræver at vi mapper terningens farver. Terningens farver kan findes ved hjælp af computervision, hvor vi får robotten til at vise alle siderne, og finder frem til terningens opbygning. 
Ved hjælp af kinematik og matrixberegninger vil vi holde styr på transformationsforholdet mellem robotten og terningen, så vi ved hvordan vi drejer hver side på terningen.
Igennem processen vil vi teste, UR robottens præcision, stress-teste terningen i forhold til hvornår det er muligt at dreje, og teste på grippperens styrke, samt succesrate.
Vi evaluerer på hastigheden, som robotten kan løse terningen på, og hvor ofte den laver fejl.


Hvordan kan en UR5‑robot programmeret i C++ autonomt manipulere og løse en Rubik’s Cube ved brug af computer vision til farvegenkendelse, Python‑baserede løsningsalgoritmer og kinematiske transformationer til korrekt orientering af terningen? Projektet undersøger, hvordan hardware‑faktorer som gripperstyrke, servo‑kontrol og robotpræcision påvirker systemets evne til at udføre stabile og nøjagtige rotationer, og evaluerer den samlede løsning ud fra hastighed, præcision og fejlrate.

