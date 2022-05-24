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
	data->nbFoodFix = data->nbFood;

	data->foodVariance = 0;

	if (data->blobs.first != NULL)
		BlobsDel(&data->blobs);
	data->blobs = BlobsInit(data->nbBlob);

	if (data->foods.first != NULL)
		FoodsDel(&data->foods);
	data->foods = FoodsInit(data->nbFood, &data->foodTex);

	GraphsInit(data);

	data->state = STATE_MENU;
}

void VarianceMore()
{
	Data *data = DataPointer();
	data->foodVariance *= 2;
	if (data->foodVariance > VARIANCE_MAX)
        	data->foodVariance = VARIANCE_MAX;
	if (data->foodVariance == 0)
		data->foodVariance = 1;
}

void VarianceLess()
{
	Data *data = DataPointer();
    	data->foodVariance /= 2;
   	if (data->foodVariance < VARIANCE_MIN)
       		data->foodVariance = VARIANCE_MIN;
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
		&ui->butt.left_2, (Vector2) { 300, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/left_arrow.png", &FoodLess
	);

	UiButtTex_init(
		&ui->butt.right_2, (Vector2) { 380, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/right_arrow.png", &FoodMore
	);

	UiButtTex_init(
		&ui->butt.left_3, (Vector2) { 480, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/left_arrow.png", &VarianceLess
	);

	UiButtTex_init(
		&ui->butt.right_3, (Vector2) { 560, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/right_arrow.png", &VarianceMore
	);


	UiButtTex_init(
		&ui->butt.restart, (Vector2) { 0, -32 }, (Vector2) { 64, 64 },
		ANCHOR_SW, "res/ui/restart.png", &RunToMenu
	);
	ui->butt.restart.color = BLANK;


	Font font = LoadFont("res/Panipuri.ttf");
	UiText_init(
		&ui->text.nbGen, "Gen : 0\0", font, 40,
		(Vector2) { 10, -80 }, ANCHOR_W, RAYWHITE
	);

	UiText_init(
		&ui->text.nbBlob, "Blobs : 4\0", font, 40,
		(Vector2) { 10, -40 }, ANCHOR_W, RAYWHITE
	);

	UiText_init(
		&ui->text.nbFood, "Carottes : 100\0", font, 40,
		(Vector2) { 10, 0 }, ANCHOR_W, RAYWHITE
	);

	UiText_init(
		&ui->text.variance, "Variance : 0\0", font, 40,
		(Vector2) { 10, 40 }, ANCHOR_W, RAYWHITE
	);
}

/*écrit un texte quand tout les blobs sont mort (est sensé mettre la simulation sur pause mais 
PUISQUE LE CODE NEST PAS COMMENT2 ONT COMPREND PAS TOUT!! SURTOUT SUR LES STRUCTURE!!!!!!*/
void UiEnd(Ui *ui)
{
	Font font = LoadFont("res/Panipuri.ttf");

	//écrit au milieu un message de fin
	UiText_init(
		&ui->text.variance, "Tout les blobs sont mort\0", font, 40,
		(Vector2) { 10, 80 }, ANCHOR_W, RAYWHITE
	);

	//debug
	printf("\n \n Tout les blobs sont mort \n \n");
}

void UiTextNbGenUpdate()
{
	Data *data = DataPointer();
	char *nbGen = 	NEW_ARR(char, 15);
	sprintf(nbGen, "Gen : %d", data->genCount);
	UiText_chngTxt(&data->ui.text.nbGen, nbGen);
	free(nbGen);
}

void UiTextNbBlobUpdate()
{
	Data *data = DataPointer();
	char *nbBlob = 	NEW_ARR(char, 23);
	sprintf(nbBlob, "Blobs : %d", data->nbBlob);
	UiText_chngTxt(&data->ui.text.nbBlob, nbBlob);
	free(nbBlob);
}

void UiTextNbFoodUpdate()
{
	Data *data = DataPointer();
	char *nbFood = 	NEW_ARR(char, 23);
	sprintf(nbFood, "Carottes : %d", data->nbFoodFix);
	UiText_chngTxt(&data->ui.text.nbFood, nbFood);
	free(nbFood);
}

void UiTextVarianceUpdate()
{
	Data *data = DataPointer();
	char *variance = NEW_ARR(char, 23);
	sprintf(variance, "Variance : %d", data->foodVariance);
	UiText_chngTxt(&data->ui.text.variance, variance);
	free(variance);
}

void UiMenuUpdate(Ui *ui)
{
	UiButtTex_update(&ui->butt.play);

	UiButtTex_update(&ui->butt.left_1);
	UiButtTex_update(&ui->butt.right_1);
	UiButtTex_update(&ui->butt.left_2);
	UiButtTex_update(&ui->butt.right_2);
	UiButtTex_update(&ui->butt.left_3);
	UiButtTex_update(&ui->butt.right_3);

	UiTextNbGenUpdate();
	UiTextNbBlobUpdate();
	UiTextNbFoodUpdate();
	UiTextVarianceUpdate();
}

void UiRunUpdate(Ui *ui)
{
	UiButtTex_update(&ui->butt.restart);

	UiButtTex_update(&ui->butt.left_1);
	UiButtTex_update(&ui->butt.right_1);
	UiButtTex_update(&ui->butt.left_2);
	UiButtTex_update(&ui->butt.right_2);
	UiButtTex_update(&ui->butt.left_3);
	UiButtTex_update(&ui->butt.right_3);

	UiTextNbGenUpdate();
	UiTextNbBlobUpdate();
	UiTextNbFoodUpdate();
	UiTextVarianceUpdate();
}

void UiRender(Ui *ui)
{
	UiButtTex_render(&ui->butt.play);

	UiButtTex_render(&ui->butt.left_1);
	UiButtTex_render(&ui->butt.right_1);
	UiButtTex_render(&ui->butt.left_2);
	UiButtTex_render(&ui->butt.right_2);
	UiButtTex_render(&ui->butt.left_3);
	UiButtTex_render(&ui->butt.right_3);

	UiButtTex_render(&ui->butt.restart);

	UiText_render(&ui->text.nbGen);
	UiText_render(&ui->text.nbBlob);
	UiText_render(&ui->text.nbFood);
	UiText_render(&ui->text.variance);
}

void UiDel(Ui *ui)
{
	UiButtTex_del(&ui->butt.play);

	UiButtTex_del(&ui->butt.left_1);
	UiButtTex_del(&ui->butt.right_1);
	UiButtTex_del(&ui->butt.left_2);
	UiButtTex_del(&ui->butt.right_2);
	
	UiButtTex_del(&ui->butt.restart);

	UiText_del(&ui->text.nbGen);
	UiText_del(&ui->text.nbBlob);
	UiText_del(&ui->text.nbFood);
	UiText_del(&ui->text.variance);
}