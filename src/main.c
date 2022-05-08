#include <stdio.h>
#include <math.h>

#include "gamemaker/core.h"
#include "gamemaker/ui/graph/graph_bar.h"
#include "blob.h"
#include "timeSpeed.h"


#define CAM_MIN_ZOOM      20
#define CAM_MAX_ZOOM     400
#define CAM_SCROLL_SPEED   0.2f
#define CAM_MOUSE_SPEED    0.002f
#define CAM_KEY_SPEED     60


struct FixUpdtData {
	float incrmnt;
	float fixDt;
	float limExec;
};

typedef struct Data {
	Cam cam;
	Blob *blob;
	int nbBlob;
	Food *food;
	int nbFood;
	TimeSpeed timeSpeed;

	// Movements avec la souris
	Vector2 beforeMouseMove;
	Vector2 mpInitial;

	struct FixUpdtData fixUdpt;

	// Statistics
	UiGraphBar speedGraph;
} Data;

Data data;

void MainInit(App *p_App)
{
	data.cam = Cam_init(10);
	TimeSpeedInit(&data.timeSpeed);
	data.nbBlob = 10;
	data.blob = BlobsInit(data.nbBlob);
	data.nbFood = 60;
	data.food = FoodsInit(data.nbFood);

	// Fixed update trucs
	data.fixUdpt.fixDt = 1.f / 60.f;
	data.fixUdpt.incrmnt = 0.f;
	data.fixUdpt.limExec = 0.2f;

	// Statistics
	data.speedGraph = UiGraphBar_default(data.nbBlob);
	data.speedGraph.anch = ANCHOR_NE;
	data.speedGraph.pos = (Vector2) { -5.f, 5.f };
	data.speedGraph.xAxis.valRng = (Vector2) { BLOB_MIN_SPEED,
		BLOB_MAX_SPEED };
	data.speedGraph.xAxis.markStep = 0.5f;
	for (int i = 0; i < data.nbBlob; i++)
		UiGraphBar_setVal(&data.speedGraph, i, data.blob[i].speed);
	UiGraphAxis_setLabel(&data.speedGraph.xAxis, "speed");
	UiGraphAxis_setLabel(&data.speedGraph.yAxis, "blob amount");
}

void FixedUpdate(const float pFixDt)
{
	for (int i = 0; i < data.nbBlob; i++) {
		// Mouvement des blobs
		Vector2 dir = BlobGetDir(data.blob[i].pos, data.food);
		data.blob[i].pos = Vector2Add(data.blob[i].pos,
			Vector2Scale(dir, pFixDt * data.blob[i].speed));

		// Detection de colision
		BlobTryEat(&data.blob[i], data.food);
	}
}

void MainUpdate(App *p_App, float p_Dt)
{
	TimeSpeedUpdate(&data.timeSpeed, &p_Dt);

	// Mouvements avec la souris
	data.cam.fov += data.cam.fov * -CAM_SCROLL_SPEED * GetMouseWheelMove();
	if (data.cam.fov < CAM_MIN_ZOOM)
		data.cam.fov = CAM_MIN_ZOOM;
	else if (data.cam.fov > CAM_MAX_ZOOM)
		data.cam.fov = CAM_MAX_ZOOM;
	
	if (IsMouseButtonPressed(0)) {
		data.mpInitial = GetMousePosition();
		data.beforeMouseMove = Cam_getPos(&data.cam);
	} else if (IsMouseButtonReleased(0) || IsMouseButtonDown(0)) {
		Vector2 mpDelta = Vector2Subtract(data.mpInitial,
			GetMousePosition());
		Vector2 newPos = Vector2Add(data.beforeMouseMove,
			Vector2Scale(mpDelta, 1.f * data.cam.fov *
				CAM_MOUSE_SPEED));
		Cam_setPos(&data.cam, newPos);
	}

	if (IsMouseButtonPressed(1)) {
		Food param = *data.food;
		param.pos = GetScreenToWorld2D(GetMousePosition(), data.cam.camera);
		param.eaten = false;
		data.food = NewFood(data.food, param);
	}
    
	// FIXED UPDATE
	data.fixUdpt.incrmnt += p_Dt * data.timeSpeed.value;

	// empêcher une boucle infinie
	if (data.fixUdpt.limExec < data.fixUdpt.incrmnt)
		data.fixUdpt.incrmnt = data.fixUdpt.limExec;

	while (data.fixUdpt.incrmnt > data.fixUdpt.fixDt) {
		FixedUpdate(data.fixUdpt.fixDt);
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

	DrawFPS(10, 10);
	TimeSpeedRender(&data.timeSpeed);
}

void MainRemove(App *p_App)
{
	if (data.blob)
		free(data.blob);
	if (data.food)
		FoodsDel(data.food);
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