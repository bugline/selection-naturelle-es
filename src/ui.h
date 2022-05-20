#ifndef UI
#define UI

#include "blob.h"
#include "gen.h"
#include "gamemaker/core.h"
#include "timeSpeed.h"
typedef struct Butt {
    UiButtTex play;
    UiButtTex restart;
    UiButtTex left;
    UiButtTex right;
} Butt;
typedef struct Ui {
    Butt butt;
} Ui;

void MenuToRun(void);
void RunToMenu(void);
void UiInit(Ui *ui);
void UiMenuUpdate(Ui *ui);
void UiRunUpdate(Ui *ui);
void UiRender(Ui *ui);
void UiDel(Ui *ui);

#endif  // UI