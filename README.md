Utilisation :
1. Générer les sources C++ via `python generator.py example.cg`
2. Copier les templates vers le dossier du code editable via `cp -R ./CPP/template/* ./CPP/custom/`
3. Copier le template de configuration de compilation vers la racine via `cp ./CPP/template/CMakeLists.txt ./`
4. Éditer le code du dossier `./CPP/custom/` et le `./CMakeLists.txt`
5. Regénérer les sources via `python generator.py example.py` : le code éditable ne sera pas écrasé !
6. Les sources en un seul fichier se trouvent dans `./generatedMono.cpp` (directement copiable dans CodingGames)
7. L'exécutable est `./bin/cg`
8. Enjoy !
  
Limitation :
* Ne pas faire attention à l'erreur `CMakeFiles/cgcode.dir/CPP/readonly/mainMono.cpp.o: file format not recognized; treating as linker script`
* Le main n'est pas modifiable pour l'instant
* On ne peut pas ajouter de fichier source pour l'instant