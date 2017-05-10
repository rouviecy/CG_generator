# CG_Generator

Features :
* Génération de code C++ pour CodinGame à partir d'un fichier de configuration simplifié
* Gestion de code en readonly et custom pour ne pas perdre après regénération le code ajouté manuellement
* Agglomération de tout le code dans un fichier unique directement uploadable vers CodinGame
* Simulation du jeu à partir du fichier Referee.java fourni par CodinGame
* Connexion au simulateur via clients TCP (netcat par exemple) ou utilisation d'un code C++ (le fichier généré précédemment par exemple)

Utilisation :
1. Se placer dans le répertoire de génération via `cd Generator`
2. Générer les sources C++ via `python generator.py Example` (la première génération complète va échouer sans les codes éditables)
3. Copier les templates vers le dossier du code editable via `cp -R ../Workspace/Example/template/* ../Workspace/Example/custom/`
4. Éditer le code du dossier `../Workspace/Example/custom/`
5. Regénérer les sources via `python generator.py Example` : le code éditable ne sera pas écrasé !
6. Les sources en un seul fichier se trouvent dans `../Workspace/Example/monolithe.cpp` (directement copiable dans CodinGame)
7. L'exécutable est `../Workspace/Example/bin/cg`
8. Enjoy !
  
Remarques :
* Ne pas faire attention à l'erreur `CMakeFiles/cgcode.dir/mainMono.cpp.o: file format not recognized; treating as linker script`
* Le main n'est pas modifiable pour l'instant
* On ne peut pas ajouter de fichier source pour l'instant
* Pour gagner du temps, s'il n'y a pas besoin de regénérer les fichiers en lecture seul, on peut compiler via `make cg` et `make cgcode` dans `../Workspace/Example/bin`