#!/bin/bash

# VARIABLES
OUT=bin/main.exe
INP='src/main.c'

INCLUDE=include/
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
gcc $INP -o $OUT -Wall -I $INCLUDE -L $LIB -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
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
