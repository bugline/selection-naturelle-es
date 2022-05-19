#ifndef STRUCT_UI
#define STRUCT_UI

#include "gamemaker/core.h"

typedef struct Butt {
    UiButtTex play;
    UiButtTex restart;
    UiButtTex nbBlobLeft;
    UiButtTex nbBlobRight;
} Butt;

typedef struct Ui {
    Butt butt;
} Ui;

#endif