#include <stdio.h>
#include <math.h>

#include "gamemaker/core.h"
#include "blob.h"


typedef struct Data {
	Cam cam;
	Blob *blob;
	int nbBlob;
	Food *food;
	int nbFood;
} Data;

Data data;


float carre(float a)  // Sérieusement ?
{
	return a * a;
}

int CollisionCircle(Vector2 pos1, float radius1, Vector2 pos2, float radius2)
{
	// Fonction non testé
	int collision = 0;

	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;

	float distanceCarre = (carre(dx) + carre(dy));

	if (distanceCarre <= carre(radius1 + radius2))
		collision = 1;

	return collision;
}

int CollisionCircleRec(Vector2 center, float radius, Rectangle rec)
{
	// Fonction non finit
	int collision = 0;

	float dx = fabsf(center.x - rec.x);
	float dy = fabsf(center.y - rec.y);

	if ((carre(dx - rec.width / 2.0f) + carre(dy - rec.width / 2.0f)))
		collision = 1;

	return collision;
}

void MainInit(App *p_App)
{
	data.cam = Cam_init(100);
	data.nbBlob = 10;
	data.blob = BlobsInit(data.nbBlob);
	data.nbFood = 10;
	data.food = FoodsInit(data.nbFood);
}

void MainUpdate(App *p_App, float p_Dt)
{
	printf("Blob(%f:%f) Carrot(%f;%f)\n", data.blob[0].pos.x, data.blob[0].pos.y, data.food[0].rec.x, data.food[0].rec.y);

	if (IsKeyDown(KEY_UP))
		data.cam.camera.target.y -= 1;
	else if (IsKeyDown(KEY_DOWN))
		data.cam.camera.target.y += 1;
	else if (IsKeyDown(KEY_LEFT))
		data.cam.camera.target.x -= 1;
	else if (IsKeyDown(KEY_RIGHT))
		data.cam.camera.target.x += 1;

	
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