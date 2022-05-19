#!/bin/bash

# VARIABLES
OUT=bin/release/project.exe
INP=`find ./ -name *.c | tr "\n" " "`

INCLUDE=inc/
LIB=lib/


# CLEAN THE PROMPT
clear


# DELETE PREVIOUS BUILD
if [ -f "$OUT" ]; then
    echo "[RUN] Deleting the previous $OUT ..."
    rm "$OUT"
    echo ""
fi


# COMPILE
echo "[RUN] Compiling $INP ..."
gcc $INP -o $OUT -Wall -O2 -D RELEASE -I $INCLUDE -L $LIB -lrayliblinux -lGL -lm -lpthread -ldl -lrt -lX11
echo ""
