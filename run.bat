@echo off


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
set ENTRIES="src\main.c"
:: le dossier où sera le .exe
set OUTPUT_DIR="bin\"
:: le .exe qui sera généré
set OUTPUT="%OUTPUT_DIR%selection_naturelle.exe"

:: le dossier où sont les .h des librairies utilisées
set INCLUDE_DIR="inc\"
:: le dossier où sont les .a des librairies utilisées
set LIB_DIR="lib\"

:: les librairies qui doivent absolument être présents (pour libraylib.a -lraylib)
set LIBS="-lraylib -lopengl32 -lgdi32 -lwinmm"
::


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
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
echo(
:: COMPILATION
%COMPILER% %ENTRIES:"=% -o %OUTPUT:"=% -Wall -D DEBUG -I %INCLUDE_DIR:"=% -L %LIB_DIR:"=% %LIBS:"=%


:: LANCEMENT DU PROGRAMME
if exist %OUTPUT% (
    echo LANCEMENT DE %OUTPUT:"=%
    %OUTPUT%
) else (
    pause
)