#ifndef UI
#define UI

#include "blob.h"
#include "gen.h"
#include "gamemaker/core.h"
#include "timeSpeed.h"

#define VARIANCE_MIN 0
#define VARIANCE_MAX 100

typedef struct Butt {
    UiButtTex play;
    UiButtTex restart;
    UiButtTex left_1;
    UiButtTex right_1;
    UiButtTex left_2;
    UiButtTex right_2;
    UiButtTex left_3;
    UiButtTex right_3;
} Butt;

typedef struct Text {
    UiText nbGen;
	UiText nbBlob;
    UiText nbFood;
    UiText variance;
    //truc que j'ai fais et que je ne sait pas a quoi ça sert car RIEN NEST COMMENTE!!!
    UiText end;
} Text;
typedef struct Ui {
    Butt butt;
    Text text;
} Ui;

void MenuToRun(void);
void RunToMenu(void);
void VarianceMore();
void VarianceLess();
void UiInit(Ui *ui);
void UiEnd(Ui *ui);
void UiTextNbGenUpdate();
void UiTextNbBlobUpdate();
void UiTextNbFoodUpdate();
void UiTextVarianceUpdate();
void UiMenuUpdate(Ui *ui);
void UiRunUpdate(Ui *ui);
void UiRender(Ui *ui);
void UiDel(Ui *ui);

#endif  // UI