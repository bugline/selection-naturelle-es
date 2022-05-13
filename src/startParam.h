#ifndef STARTPARAM
#define STARTPARAM

#include "gamemaker/core.h"

typedef struct StartParamButt {
    UiButtTex play;
    UiButtTex pause;
    UiButtTex nbBlobLeft;
    UiButtTex nbBlobRight;
} StartParamButt;

typedef struct StartParam {
    StartParamButt butt;
} StartParam;

void StartParamInit(StartParam *sp);
void StartParamUpdate(StartParam *sp);
void StartParamRender(StartParam *sp);
void StartParamDel(StartParam *sp);


void StartParamInit(StartParam *sp)
{
    UiButtTex_init(&sp->butt.play, (Vector2) { 0, -32 }, (Vector2) { 64, 64 }
        , ANCHOR_SW, "res/ui/play.png", NULL);

    UiButtTex_init(&sp->butt.nbBlobLeft, (Vector2) { 120, -32 }
        , (Vector2) { 64, 64 }, ANCHOR_SW, "res/ui/left_arrow.png", NULL);
    UiButtTex_init(&sp->butt.nbBlobRight, (Vector2) { 200, -32 }
        , (Vector2) { 64, 64 }, ANCHOR_SW, "res/ui/right_arrow.png", NULL);
}

void StartParamUpdate(StartParam *sp)
{
    UiButtTex_update(&sp->butt.play);

    UiButtTex_update(&sp->butt.nbBlobLeft);
    UiButtTex_update(&sp->butt.nbBlobRight);
}

void StartParamRender(StartParam *sp)
{
    UiButtTex_render(&sp->butt.play);

    UiButtTex_render(&sp->butt.nbBlobLeft);
    UiButtTex_render(&sp->butt.nbBlobRight);
}

void StartParamDel(StartParam *sp)
{
    UiButtTex_del(&sp->butt.play);

    UiButtTex_del(&sp->butt.nbBlobLeft);
    UiButtTex_del(&sp->butt.nbBlobRight);
}

// STARTPARAM
#endif