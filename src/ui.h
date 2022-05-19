#ifndef UI
#define UI

#include "structUi.h"
#include "data.h"
#include "blob.h"
#include "gen.h"

void MenuToRun(Data *data);
void RunToMenu(Data * data);
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