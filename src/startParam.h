#ifndef STARTPARAM
#define STARTPARAM

#include "gamemaker/core.h"

typedef struct StartParam {
    UiButtTex play_butt;
    UiButtTex nbBlobLeft_butt;
    UiButtTex nbBlobRight_butt;
} StartParam;

void StartParamInit(StartParam *sp);
void StartParamUpdate(StartParam *sp);
void StartParamRender(StartParam *sp);
void StartParamDel(StartParam *sp);


void StartParamInit(StartParam *sp)
{
    UiButtTex_init(&sp->play_butt, (Vector2) { 0, -50 }, (Vector2) { 128, 128 }
        , ANCHOR_S, "res/play-button.png", NULL);

    UiButtTex_init(&sp->nbBlobLeft_butt, (Vector2) { 150, -50 }
        , (Vector2) { 128, 128 }, ANCHOR_S, "res/play-button.png", NULL);
    UiButtTex_init(&sp->nbBlobRight_butt, (Vector2) { 0, -50 }
        , (Vector2) { 128, 128 }, ANCHOR_S, "res/play-button.png", NULL);


}

void StartParamUpdate(StartParam *sp)
{
    UiButtTex_update(&sp->play_butt);
}

void StartParamRender(StartParam *sp)
{
    UiButtTex_render(&sp->play_butt);
}

void StartParamDel(StartParam *sp)
{
    UiButtTex_del(&sp->play_butt);
}

// STARTPARAM
#endif