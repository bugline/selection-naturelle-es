#include "ui.h"
#include "data.h"


void MenuToRun()
{
	Data *data = DataPointer();

	data->ui.butt.play.color = BLANK;
	data->ui.butt.restart.color = WHITE;

	data->ui.butt.left_1.mButt.callback = &TimeSpeedLess;
	data->ui.butt.right_1.mButt.callback = &TimeSpeedMore;

	data->state = STATE_RUN;
}

void RunToMenu()
{
	Data *data = DataPointer();

	data->ui.butt.play.color = WHITE;
	data->ui.butt.restart.color = BLANK;

	data->ui.butt.left_1.mButt.callback = &BlobLess;
	data->ui.butt.right_1.mButt.callback = &BlobMore;

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

void UiInit(Ui *ui)
{
	UiButtTex_init(
		&ui->butt.play, (Vector2) { 0, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/play.png", &MenuToRun
	);

	UiButtTex_init(
		&ui->butt.left_1, (Vector2) { 120, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/left_arrow.png", &BlobLess
	);

	UiButtTex_init(
		&ui->butt.right_1, (Vector2) { 200, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/right_arrow.png", &BlobMore
	);

	UiButtTex_init(
		&ui->butt.restart, (Vector2) { 0, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/restart.png", &RunToMenu
	);
	ui->butt.restart.color = BLANK;

	Font font = LoadFont("res/Panipuri.ttf");
	UiText_init(
		&ui->text.nbBlob, "4\0", font, 50,
		(Vector2) { 10, 0 }, ANCHOR_W, RAYWHITE
	);
}

void UiTextNbBlobUpdate()
{
	Data *data = DataPointer();
	char *nbBlob = 	NEW_ARR(char, 11);
	sprintf(nbBlob, "Blob: %d", data->nbBlob);
	UiText_chngTxt(&data->ui.text.nbBlob, nbBlob);
	free(nbBlob);
}

void UiMenuUpdate(Ui *ui)
{
	UiButtTex_update(&ui->butt.play);

	UiButtTex_update(&ui->butt.left_1);
	UiButtTex_update(&ui->butt.right_1);

	UiTextNbBlobUpdate();
}

void UiRunUpdate(Ui *ui)
{
	UiButtTex_update(&ui->butt.restart);

	UiButtTex_update(&ui->butt.left_1);
	UiButtTex_update(&ui->butt.right_1);

	UiTextNbBlobUpdate();
}

void UiRender(Ui *ui)
{
	UiButtTex_render(&ui->butt.play);

	UiButtTex_render(&ui->butt.left_1);
	UiButtTex_render(&ui->butt.right_1);

	UiButtTex_render(&ui->butt.restart);

	UiText_render(&ui->text.nbBlob);
}

void UiDel(Ui *ui)
{
	UiButtTex_del(&ui->butt.play);

	UiButtTex_del(&ui->butt.left_1);
	UiButtTex_del(&ui->butt.right_1);
	
	UiButtTex_del(&ui->butt.restart);

	UiText_del(&ui->text.nbBlob);
}