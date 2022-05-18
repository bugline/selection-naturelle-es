#ifndef UI
#define UI

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

// void ButtCallback_play();
// void ButtCallback_nbBlobLeft();
// void ButtCallback_nbBlobRight();

void UiMenuInit(Ui *ui);
void UiRunInit(Ui *ui);
void UiUpdate(Ui *ui);
void UiRender(Ui *ui);
void UiDel(Ui *ui);

#endif  // UI