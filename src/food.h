#ifndef FOOD
#define FOOD

#include <stdbool.h>
#include "raylib.h"
#include "gamemaker/core.h"


typedef struct Food {
	Vector2 pos;
	Vector2 size;
	Texture2D *tex;
	bool eaten;
} Food;


bool FoodCircleColl(const Food *food, const Vector2 circleCenter,
	const float radius);
void FoodDraw(const Food *food);

// Arrays
Food *FoodsInit(int nbFood);
void FoodsRender(Food *foods, int nbFood);
void FoodsDel(Food *foods);


// IMPLEMENTATION

bool FoodCircleColl(const Food *pFood, const Vector2 pCircPos, const float pRad)
{
	float sqrdDist = Vector2LengthSqr(Vector2Subtract(pCircPos,
		pFood->pos));
	if (sqrdDist > pRad * pRad)
		return false;

	return true;
}

void FoodDraw(const Food *food)
{
	DrawTexMid(*food->tex, food->pos, food->size);
}

// Array functions

Food *FoodsInit(int nbFood)
{
	Texture2D *tex = NEW(Texture2D);
	*tex = LoadTexture("res/food.png");
	Food *foods = NEW_ARR(Food, nbFood);
	float width = 0.4f;
	float height = 0.4f;

	for (int i = 0; i < nbFood; i++) {
		foods[i].pos.x = GetRandomValue(-50, 50);
		foods[i].pos.y = GetRandomValue(-50, 50);
		foods[i].size = (Vector2) { width, height };
		foods[i].tex = tex;
		foods[i].eaten = false;
	}
	return foods;
}

void FoodsRender(Food *foods, int nbFood)
{
	for (int i = 0; i < nbFood; i++) {
		if (!foods[i].eaten) {
			FoodDraw(&foods[i]);
		}
	}
}

void FoodsDel(Food *foods)
{
	free(foods[0].tex);
	free(foods);
}


#endif  // FOOD