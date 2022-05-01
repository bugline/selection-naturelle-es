#include <stdio.h>
#include <math.h>

#include "gamemaker/core.h"
#include "blob.h"
#include "speed.h"


#define CAM_MIN_ZOOM      20
#define CAM_MAX_ZOOM     400
#define CAM_SCROLL_SPEED   0.2f
#define CAM_MOUSE_SPEED    0.002f
#define CAM_KEY_SPEED     60


typedef struct Data {
	Cam cam;
	Blob *blob;
	int nbBlob;
	Food *food;
	int nbFood;
	Speed speed;

	Vector2 beforeMouseMove;
	Vector2 mpInitial;
} Data;

Data data;

void MainInit(App *p_App)
{
	data.cam = Cam_init(10);
	SpeedInit(&data.speed);
	data.nbBlob = 10;
	data.blob = BlobsInit(data.nbBlob);
	data.nbFood = 10;
	data.food = FoodsInit(data.nbFood);
}

void MainUpdate(App *p_App, float p_Dt)
{
	//printf("Blob(%f:%f) Carrot(%f;%f)\n", data.blob[0].pos.x, data.blob[0].pos.y, data.food[0].rec.x, data.food[0].rec.y);
	SpeedUpdate(&data.speed, &p_Dt);

	if (IsKeyDown(KEY_UP))
		data.cam.camera.target.y -= CAM_KEY_SPEED * p_Dt;
	else if (IsKeyDown(KEY_DOWN))
		data.cam.camera.target.y += CAM_KEY_SPEED * p_Dt;
	else if (IsKeyDown(KEY_LEFT))
		data.cam.camera.target.x -= CAM_KEY_SPEED * p_Dt;
	else if (IsKeyDown(KEY_RIGHT))
		data.cam.camera.target.x += CAM_KEY_SPEED * p_Dt;

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

	// Mouvement des blobs
	for (int i = 0; i < data.nbBlob; i++) {
		Vector2 dir = BlobGetDir(data.blob[i].pos, data.food,
			data.nbFood);
		data.blob[i].pos = Vector2Add(data.blob[i].pos, Vector2Scale(dir, p_Dt * 5));
	}
}

void MainRender(App *p_App)
{
	Cam_start(&data.cam, p_App);

	BlobsRender(data.blob, data.nbBlob);
	FoodsRender(data.food, data.nbFood);
	
	Cam_stop();

	DrawFPS(10, 10);
	SpeedRender(&data.speed);
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

	App *app = App_new(param);

	App_setInit(app, &MainInit);
	App_setUpdate(app, &MainUpdate);
	App_setRender(app, &MainRender);
	App_setRemove(app, &MainRemove);

	App_loop(app);
	App_del(app);
	
	return 0;
}