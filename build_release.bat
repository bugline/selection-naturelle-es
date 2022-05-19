@echo off

:: Compiller pour la distribution


:: STRUCTURE DU DOSSIER
:: |
:: |`-bin\
:: |   `-mon_super_programme.exe
:: |`-include\
:: |  |`-h_de_librairie1.h
:: |   `-h_de_librairie2.h
:: |`-lib\
:: |  |`-a_de_librairie1.a
:: |   `-a_de_librairie2.a
:: |`-src\
:: |  |`-main.c
:: |   `-second_fichier.c
::  `-run.bat


:: VARIABLES
set COMPILER="T:\1G 4\DESSARDM\NSI_Malo-Dessard\mingw-w64\mingw\bin\gcc.exe"

:: entrées (tous les fichers .c (pas les .h) séparés par un espace)
set ENTRIES="./src/gen.c ./src/blob.c ./src/ui.c ./src/timeSpeed.c ./src/mouse.c ./src/food.c ./src/data.c ./src/linked_list.c ./src/main.c ./inc/gamemaker/window.c ./inc/gamemaker/cam.c ./inc/gamemaker/app.c ./inc/gamemaker/ui/button/butt.c ./inc/gamemaker/ui/button/tex.c ./inc/gamemaker/ui/button/text.c ./inc/gamemaker/ui/graph/line.c ./inc/gamemaker/ui/graph/graph.c ./inc/gamemaker/ui/graph/bar.c ./inc/gamemaker/ui/panel.c ./inc/gamemaker/ui/img.c ./inc/gamemaker/ui/text.c ./inc/gamemaker/ui/anchor.c ./inc/gamemaker/draw.c ./inc/gamemaker/param.c"
:: le dossier où sera le .exe
set OUTPUT_DIR="bin\release\"
:: le .exe qui sera généré
set OUTPUT="%OUTPUT_DIR%selection_naturelle.exe"

:: le dossier où sont les .h des librairies utilisées
set INCLUDE_DIR="inc\"
:: le dossier où sont les .a des librairies utilisées
set LIB_DIR="lib\"

:: les librairies qui doivent absolument être présents (pour libraylib.a -lraylib)
set LIBS="-lraylib -lopengl32 -lgdi32 -lwinmm"


:: CREATION DES DOSSIER NON EXISTANTS

:: dossier du .exe
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

:: dossier des librairies
if not exist %INCLUDE_DIR% mkdir %INCLUDE_DIR%
if not exist %LIB_DIR% mkdir %LIB_DIR%


:: NETOYAGE
:: netoyer l'écran
cls

:: suppretion de l'ancien executable
if exist %OUTPUT% del %OUTPUT%

echo(

:: COMPILATION
%COMPILER% %ENTRIES:"=% -o %OUTPUT:"=% -O2 -Wall -D RELEASE -I %INCLUDE_DIR:"=% -L %LIB_DIR:"=% %LIBS:"=%