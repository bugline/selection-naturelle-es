// #define RELEASE

#include <stdio.h>
#include <math.h>

#include "gamemaker/core.h"
#include "blob.h"
#include "timeSpeed.h"
#include "gen.h"
#include "data.h"
#include "mouse.h"
#include "startParam.h"

Data data;

void MainInit(App *p_App)
{
	data.cam = Cam_init(10);

	StartParamInit(&data.startParam);

	TimeSpeedInit(&data.timeSpeed);

	data.nbBlob = 4;
	data.blobs = BlobsInit(data.nbBlob);

	data.nbFood = 100;
	data.foodTex = LoadTexture("res/food.png");
	data.foods = FoodsInit(data.nbFood, &data.foodTex);

	// Fixed update trucs
	data.fixUdpt.fixDt = 1.f / 60.f;
	data.fixUdpt.incrmnt = 0.f;
	data.fixUdpt.limExec = 0.2f;

	GraphsInit(&data);
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

void MainUpdate(App *p_App, float p_Dt)
{
	StartParamUpdate(&data.startParam);

	TimeSpeedUpdate(&data.timeSpeed, &p_Dt);

	MouseUpdate(&data);
    
	// FIXED UPDATE
	data.fixUdpt.incrmnt += p_Dt * data.timeSpeed.value;

	// empêcher une boucle infinie
	if (data.fixUdpt.limExec < data.fixUdpt.incrmnt)
		data.fixUdpt.incrmnt = data.fixUdpt.limExec;

	while (data.fixUdpt.incrmnt > data.fixUdpt.fixDt) {
		FixedUpdate(data.fixUdpt.fixDt, &data);
		data.fixUdpt.incrmnt -= data.fixUdpt.fixDt;
	}
}

void MainRender(App *p_App)
{
	Cam_start(&data.cam, p_App);

	FoodsRender(&data.foods);
	BlobsRender(&data.blobs);
	
	Cam_stop();

	UiGraphBar_render(&data.speedGraph);
	UiGraphLine_render(&data.popGraph);

	DrawFPS(10, 10);
	TimeSpeedRender(&data.timeSpeed);

	StartParamRender(&data.startParam);
}

void MainRemove(App *p_App)
{
	StartParamDel(&data.startParam);

	TimeSpeedDel(&data.timeSpeed);

	BlobsDel(&data.blobs);
	FoodsDel(&data.foods);

	UiGraphBar_del(&data.speedGraph);
	UiGraphLine_del(&data.popGraph);

	UnloadTexture(data.foodTex);
}

int main()
{
	App_param param = App_param_default();
	param.update.fps = 0;
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