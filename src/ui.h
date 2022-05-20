#ifndef UI
#define UI

#include "blob.h"
#include "gen.h"
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

void MenuToRun(void);
void RunToMenu(void);
void ButtCallback_play();
void ButtCallback_nbBlobLeft();
void ButtCallback_nbBlobRight();
void ButtCallback_restart();
void UiInit(Ui *ui);
void UiMenuUpdate(Ui *ui);
void UiRunUpdate(Ui *ui);
void UiRender(Ui *ui);
void UiDel(Ui *ui);

#endif  // UI