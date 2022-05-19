#!/bin/bash

# VARIABLES
OUT=bin/selection_naturelle.exe
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
gcc $INP -o $OUT -Wall -D DEBUG -I $INCLUDE -L $LIB -lrayliblinux -lGL -lm -lpthread -ldl -lrt -lX11
echo ""


# RUN
if [ -f "$OUT" ]; then
    echo "[RUN] Running $OUT ..."
    exec $OUT
    echo ""
else
    echo "[RUN] Compilation of $INP failed !"
    echo ""
fi
