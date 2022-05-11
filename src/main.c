// #define RELEASE

#include <stdio.h>
#include <math.h>

#include "gamemaker/core.h"
#include "blob.h"
#include "timeSpeed.h"
#include "gen.h"
#include "data.h"
#include "mouse.h"

Data data;

void MainInit(App *p_App)
{
	data.cam = Cam_init(10);

	TimeSpeedInit(&data.timeSpeed);

	data.nbBlob = 4;
	data.blob = BlobsInit(data.nbBlob);

	data.nbFood = 100;
	data.foodTex = LoadTexture("res/food.png");
	data.food = FoodsInit(data.nbFood, &data.foodTex);

	// Fixed update trucs
	data.fixUdpt.fixDt = 1.f / 60.f;
	data.fixUdpt.incrmnt = 0.f;
	data.fixUdpt.limExec = 0.2f;

	GraphsInit(&data);
}

void FixedUpdate(const float pFixDt, Data *pData)
{
	for (int i = 0; i < pData->nbBlob; i++) {
		// Mouvement des blobs
		Vector2 dir = BlobGetDir(pData->blob[i].pos, pData->food);
		pData->blob[i].pos = Vector2Add(pData->blob[i].pos,
			Vector2Scale(dir, pFixDt * pData->blob[i].speed));

		// Detection de colision
		BlobTryEat(&pData->blob[i], pData->food);
	}

	if (AreAllFoodsGone(pData->food)) {
		ProduceNextGen(pData);
		GraphsUpdate(pData);
		FoodsDel(pData->food);
		pData->food = FoodsInit(pData->nbFood, &pData->foodTex);
	}
}

void MainUpdate(App *p_App, float p_Dt)
{
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

	FoodsRender(data.food);
	BlobsRender(data.blob, data.nbBlob);
	
	Cam_stop();

	UiGraphBar_render(&data.speedGraph);
	UiGraphLine_render(&data.popGraph);

	DrawFPS(10, 10);
	TimeSpeedRender(&data.timeSpeed);
}

void MainRemove(App *p_App)
{
	if (data.blob)
		free(data.blob);
	if (data.food)
		FoodsDel(data.food);

	UiGraphBar_del(&data.speedGraph);
	UiGraphLine_del(&data.popGraph);

	UnloadTexture(data.foodTex);
}

int main()
{
	App_param param = App_param_default();
	param.update.fps = 0;

	App *app = App_new(param);

	App_setInit(app, &MainInit);
	App_setUpdate(app, &MainUpdate);
	App_setRender(app, &MainRender);
	App_setRemove(app, &MainRemove);

	App_loop(app);
	App_del(app);
	
	return 0;
}