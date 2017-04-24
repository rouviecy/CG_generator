Utilisation :
1. Générer les sources C++ via `python generator.py example.py`
2. Copier les templates vers le dossier du code editable via `cp -R CPP/template/* CPP/custom/`
3. Copier le template de configuration de compilation vers la racine via `cp CPP/template/CMakeLists.txt ./`
4. Éditer le code du dossier `CPP/custom` et le `./CMakeLists.txt`
5. Regénérer les sources readonly si besoin est via `python generator.py example.py` : le code éditable ne sera pas écrasé !
6. Compiler via `mkdir bin; cd bin; cmake ..; make;`
7. Enjoy !