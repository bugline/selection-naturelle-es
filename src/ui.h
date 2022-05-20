#ifndef UI
#define UI

#include "blob.h"
#include "gen.h"
#include "gamemaker/core.h"
#include "timeSpeed.h"
typedef struct Butt {
    UiButtTex play;
    UiButtTex restart;
    UiButtTex left_1;
    UiButtTex right_1;
} Butt;

typedef struct Text {
	UiText nbBlob;
} Text;
typedef struct Ui {
    Butt butt;
    Text text;
} Ui;

void MenuToRun(void);
void RunToMenu(void);
void UiInit(Ui *ui);
void UiMenuUpdate(Ui *ui);
void UiRunUpdate(Ui *ui);
void UiRender(Ui *ui);
void UiDel(Ui *ui);

#endif  // UI