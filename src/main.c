// #define RELEASE

#include <stdio.h>
#include <math.h>

#include "gamemaker/core.h"
#include "blob.h"
#include "timeSpeed.h"
#include "gen.h"
#include "data.h"
#include "mouse.h"
#include "ui.h"

#define STATE_MENU 1
#define STATE_RUN 2



void RestartInit(Data *data)
{
	if (data->blobs.first != NULL)
		BlobsDel(&data->blobs);
	data->blobs = BlobsInit(data->nbBlob);
	if (data->foods.first != NULL)
		FoodsDel(&data->foods);
	data->foods = FoodsInit(data->nbFood, &data->foodTex);

	GraphsInit(data);
}

void MainInit(App *p_App)
{
	Data *data = DataPointer();
	data->cam = Cam_init(10);

	data->state = STATE_MENU;

	UiMenuInit(&data->ui);

	TimeSpeedInit(&data->timeSpeed);

	data->nbBlob = 4;
	
	data->nbFood = 100;
	data->foodTex = LoadTexture("res/food.png");
	

	// Fixed update trucs
	data->fixUdpt.fixDt = 1.f / 60.f;
	data->fixUdpt.incrmnt = 0.f;
	data->fixUdpt.limExec = 0.2f;

	RestartInit(data);
}

void FixedUpdate(const float pFixDt, Data *pData)
{
	Iter iter = Iterate(&pData->blobs);
	Blob *blob = Iter_getElem(Blob, &iter);

	while (blob != NULL) {
		// Mouvement des blobs
		Vector2 dir = BlobGetDir(blob->pos, &pData->foods);
		blob->pos = Vector2Add(blob->pos, Vector2Scale(dir,
			pFixDt * blob->speed));

		// Detection de colision
		BlobTryEat(blob, &pData->foods);

		Iter_next(&iter);
		blob = Iter_getElem(Blob, &iter);
	}

	// Quand toutes les carotes sont mangées
	if (pData->foods.first == NULL) {
		ProduceNextGen(pData);
		GraphsUpdate(pData);
		FoodsDel(&pData->foods);
		pData->foods = FoodsInit(pData->nbFood, &pData->foodTex);
	}
}

void MenuUpdate(Data *data)
{
	UiUpdate(&data->ui);

	MouseUpdate(data);
}

void RunUpdate(Data *data, float p_Dt)
{
	TimeSpeedUpdate(&data->timeSpeed, &p_Dt);

	MouseUpdate(data);
    
	// FIXED UPDATE
	data->fixUdpt.incrmnt += p_Dt * data->timeSpeed.value;

	// empêcher une boucle infinie
	if (data->fixUdpt.limExec < data->fixUdpt.incrmnt)
		data->fixUdpt.incrmnt = data->fixUdpt.limExec;

	while (data->fixUdpt.incrmnt > data->fixUdpt.fixDt) {
		FixedUpdate(data->fixUdpt.fixDt, data);
		data->fixUdpt.incrmnt -= data->fixUdpt.fixDt;
	}
}

void MainUpdate(App *p_App, float p_Dt)
{
	Data *data = DataPointer();
	if (data->state == STATE_MENU) {
		MenuUpdate(data);
	}
	else if (data->state == STATE_RUN) {
		RunUpdate(data, p_Dt);
	}
}

void MainRender(App *p_App)
{
	Data *data = DataPointer();
	Cam_start(&data->cam, p_App);

	FoodsRender(&data->foods);
	BlobsRender(&data->blobs);
	
	Cam_stop();

	UiGraphBar_render(&data->speedGraph);
	UiGraphLine_render(&data->popGraph);

	DrawFPS(10, 10);
	TimeSpeedRender(&data->timeSpeed);

	UiRender(&data->ui);
}

void MainRemove(App *p_App)
{
	Data *data = DataPointer();
	UiDel(&data->ui);

	TimeSpeedDel(&data->timeSpeed);

	BlobsDel(&data->blobs);
	FoodsDel(&data->foods);

	UiGraphBar_del(&data->speedGraph);
	UiGraphLine_del(&data->popGraph);

	UnloadTexture(data->foodTex);
}

int main()
{
	App_param param = App_param_default();
	param.update.fps = 0;
	param.render.limitFPS = 1.f / 60.f;
	param.window.autoResize = false;

	App *app = App_new(param);

	App_setInit(app, &MainInit);
	App_setUpdate(app, &MainUpdate);
	App_setRender(app, &MainRender);
	App_setRemove(app, &MainRemove);

	App_loop(app);
	App_del(app);
	
	return 0;
}