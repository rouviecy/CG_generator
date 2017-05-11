# CG_Generator

### Features
* Génération de code C++ pour CodinGame à partir d'un fichier de configuration simplifié
* Gestion de code en readonly et custom pour ne pas perdre après regénération le code ajouté manuellement
* Agglomération de tout le code dans un fichier unique directement uploadable vers CodinGame
* Simulation du jeu à partir du fichier Referee.java fourni par CodinGame
* Connexion au simulateur via clients TCP (netcat par exemple) ou utilisation d'un exécutable (le fichier C++ généré précédemment par exemple)

## Generator

### Utilisation

1. Se placer dans le répertoire de génération via `cd Generator`
2. Générer les sources C++ via `python generator.py Example` (la première génération complète va échouer sans les codes éditables)
3. Copier les templates vers le dossier du code editable via `cp -R ../Workspace/Example/template/* ../Workspace/Example/custom/`
4. Éditer le code du dossier `../Workspace/Example/custom/`
5. Regénérer les sources via `python generator.py Example` : le code éditable ne sera pas écrasé !
6. Les sources en un seul fichier se trouvent dans `../Workspace/Example/monolithe.cpp` (directement copiable dans CodinGame)
7. L'exécutable est `../Workspace/Example/bin/cg`
8. Enjoy !
  
### Remarques

* Ne pas faire attention à l'erreur `CMakeFiles/cgcode.dir/mainMono.cpp.o: file format not recognized; treating as linker script`
* Le main n'est pas modifiable pour l'instant
* On ne peut pas ajouter de fichier source pour l'instant
* Pour gagner du temps, s'il n'y a pas besoin de regénérer les fichiers en lecture seul, on peut compiler via `make cg` et `make cgcode` dans `../Workspace/Example/bin`

## Simulator

### Utilisation

1. Se placer dans le répertoire de simulation via `cd Simulator`
2. Importer le fichier `Referee.java` fourni par CodinGame
3. Régler les paramètres du simulateur dans `MultiReferee.java` (méthode `Initialiser()`)
4. Générer le simulateur via `make` (cela compile également deux exemples de joueurs)
5. Lancer dans une console le simulateur via `java Referee`
6. Pour chaque joueur, lancer dans une console un client via `./client executable ip port` avec :
    * `executable` le chemin vers l'exécutable joueur
    * `ip` l'adresse IP du serveur de simulation (ici 127.0.0.1)
    * `port` le port du serveur de simulation (4200 pour le premier joueur, 4201 pour le deuxième joueur, etc.)
7. Lorsque tous les joueurs sont connectés, la simulation se lance et donne le classement en sortie console (TODO : API de multi-run et algorithmes génétiques)

## Interactions

![Interactions](https://raw.githubusercontent.com/rouviecy/CG_generator/master/interactions.png)