#ifndef UI
#define UI

#include "data.h"
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

void ButtCallback_play();
void ButtCallback_nbBlobLeft();
void ButtCallback_nbBlobRight();

void UiMenuInit(Ui *ui);
void UiRunInit(Ui *ui);
void UiUpdate(Ui *ui);
void UiRender(Ui *ui);
void UiDel(Ui *ui);


void ButtCallback_play()
{
    Data *data = DataPointer();
}

void ButtCallback_nbBlobLeft()
{
    Data *data = DataPointer();
}

void ButtCallback_nbBlobRight()
{
    //Data *data = DataPointer();
}

void UiMenuInit(Ui *ui)
{
    UiButtTex_init(
        &ui->butt.play, (Vector2) { 0, -32 }, (Vector2) { 64, 64 },
        ANCHOR_SW, "res/ui/play.png", &ButtCallback_play
    );

    UiButtTex_init(
        &ui->butt.nbBlobLeft, (Vector2) { 120, -32 }, (Vector2) { 64, 64 },
        ANCHOR_SW, "res/ui/left_arrow.png", &ButtCallback_nbBlobLeft
    );

    UiButtTex_init(
        &ui->butt.nbBlobRight, (Vector2) { 200, -32 }, (Vector2) { 64, 64 },
        ANCHOR_SW, "res/ui/right_arrow.png", &ButtCallback_nbBlobRight
    );
}



void UiRunInit(Ui *ui)
{

}

void UiUpdate(Ui *ui)
{
    UiButtTex_update(&ui->butt.play);

    UiButtTex_update(&ui->butt.nbBlobLeft);
    UiButtTex_update(&ui->butt.nbBlobRight);
}

void UiRender(Ui *ui)
{
    UiButtTex_render(&ui->butt.play);

    UiButtTex_render(&ui->butt.nbBlobLeft);
    UiButtTex_render(&ui->butt.nbBlobRight);
}

void UiDel(Ui *ui)
{
    UiButtTex_del(&ui->butt.play);

    UiButtTex_del(&ui->butt.nbBlobLeft);
    UiButtTex_del(&ui->butt.nbBlobRight);
}

// UI
#endif