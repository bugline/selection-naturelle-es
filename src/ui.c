#include "ui.h"
#include "data.h"
#include "gen.h"


void MenuToRun()
{
	Data *data = DataPointer();

	data->ui.butt.play.color = BLANK;
	data->ui.butt.nbBlobLeft.color = BLANK;
	data->ui.butt.nbBlobRight.color = BLANK;

	data->ui.butt.restart.color = WHITE;

	data->state = STATE_RUN;
}

void RunToMenu()
{
	Data *data = DataPointer();

	data->ui.butt.play.color = WHITE;
	data->ui.butt.nbBlobLeft.color = WHITE;
	data->ui.butt.nbBlobRight.color = WHITE;
	data->ui.butt.restart.color = BLANK;

	data->timeSpeed.value = 1;
	data->nbBlob = 4;
	data->nbFood = 100;

	if (data->blobs.first != NULL)
		BlobsDel(&data->blobs);
	data->blobs = BlobsInit(data->nbBlob);

	if (data->foods.first != NULL)
		FoodsDel(&data->foods);
	data->foods = FoodsInit(data->nbFood, &data->foodTex);

	GraphsInit(data);

	data->state = STATE_MENU;
}

void ButtCallback_play()
{
	MenuToRun();
}

void ButtCallback_nbBlobLeft()
{
	Data *data = DataPointer();
	BlobLess(&data->nbBlob, &data->blobs);

	UiGraphBar_del(&data->speedGraph);
	UiGraphLine_del(&data->popGraph);

	GraphsInit();
}

void ButtCallback_nbBlobRight()
{
	Data *data = DataPointer();
	BlobMore(&data->nbBlob, &data->blobs);

	UiGraphBar_del(&data->speedGraph);
	UiGraphLine_del(&data->popGraph);

	GraphsInit();
}

void ButtCallback_restart()
{
	RunToMenu();
}

void UiInit(Ui *ui)
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

	UiButtTex_init(
	&ui->butt.restart, (Vector2) { 0, -32 }, (Vector2) { 64, 64 },
	ANCHOR_SW, "res/ui/restart.png", &ButtCallback_restart
	);
	ui->butt.restart.color = BLANK;
}

void UiMenuUpdate(Ui *ui)
{
	UiButtTex_update(&ui->butt.play);
	UiButtTex_update(&ui->butt.nbBlobLeft);
	UiButtTex_update(&ui->butt.nbBlobRight);
}

void UiRunUpdate(Ui *ui)
{
	UiButtTex_update(&ui->butt.restart);
}

void UiRender(Ui *ui)
{
	UiButtTex_render(&ui->butt.play);
	UiButtTex_render(&ui->butt.nbBlobLeft);
	UiButtTex_render(&ui->butt.nbBlobRight);

	UiButtTex_render(&ui->butt.restart);
}

void UiDel(Ui *ui)
{
	UiButtTex_del(&ui->butt.play);
	UiButtTex_del(&ui->butt.nbBlobLeft);
	UiButtTex_del(&ui->butt.nbBlobRight);
	
	UiButtTex_del(&ui->butt.restart);
}