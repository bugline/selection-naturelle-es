#include <stdio.h>
#include <math.h>

#include "gamemaker/core.h"
#include "blob.h"


typedef struct Blob {
	float size;
	Vector2 pos;
	Color color;
} Blob;

typedef struct Food {
	Rectangle rec;
	Texture2D *tex;
} Food;

typedef struct Data {
	Cam cam;
	Blob *blob;
	int nbBlob;
	Food *food;
	int nbFood;
} Data;

Data data;

Blob *BlobsInit(int nbBlob)
{
	Blob *blobs = NEW_ARR(Blob, nbBlob);
	for (int i = 0; i < nbBlob; i++) {
		blobs[i].size = 5;
		float posX = GetRandomValue(-50, 50);
		float posY = GetRandomValue(-50, 50);
		blobs[i].pos = (Vector2) { posX, posY };
		blobs[i].color = (Color) { 255, 50, 50, 255 };
	}
	return blobs;
}

void BlobsDel(Blob *blobs)
{
	free(blobs);
}

void DrawBlob(Blob blob)
{
	DrawCircle(blob.pos.x, blob.pos.y, blob.size, blob.color);
}

void BlobsRender(Blob *blobs, int nbBlob)
{
	for (int i = 0; i < nbBlob; i++) {
		DrawBlob(blobs[i]);
	}
}

Food *FoodsInit(int nbFood)
{
	Texture2D *tex = NEW(Texture2D);
	*tex = LoadTexture("res/food.png");
	Food *foods = NEW_ARR(Food, nbFood);
	float width = 3;
	float height = 3;

	for (int i = 0; i < nbFood; i++) {
		float posX = GetRandomValue(-50, 50);
		float posY = GetRandomValue(-50, 50);
		foods[i].rec = (Rectangle) { posX, posY, width, height };
		foods[i].tex = tex;
	}
	return foods;
}

void FoodsDel(Food *foods)
{
	free(foods[0].tex);
	free(foods);
}

void FoodDraw(Food food)
{
	DrawTexMid(*food.tex, food.rec);
}

void FoodsRender(Food *foods, int nbFood)
{
	for (int i = 0; i < nbFood; i++) {
		FoodDraw(foods[i]);
	}
}

float carre(float a)
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
	if (IsKeyDown(KEY_UP))
		data.cam.camera.target.y -= 1;
	else if (IsKeyDown(KEY_DOWN))
		data.cam.camera.target.y += 1;
	else if (IsKeyDown(KEY_LEFT))
		data.cam.camera.target.x -= 1;
	else if (IsKeyDown(KEY_RIGHT))
		data.cam.camera.target.x += 1;
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