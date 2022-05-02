#ifndef FOOD
#define FOOD

#include "raylib.h"
#include "gamemaker/core.h"


typedef struct Food {
	Vector2 pos;
	Vector2 size;
	Texture2D *tex;
} Food;


void FoodDraw(const Food *food);

// Arrays
Food *FoodsInit(int nbFood);
void FoodsRender(Food *foods, int nbFood);
void FoodsDel(Food *foods);


// IMPLEMENTATION

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
	}
	return foods;
}

void FoodsRender(Food *foods, int nbFood)
{
	for (int i = 0; i < nbFood; i++) {
		FoodDraw(&foods[i]);
	}
}

void FoodsDel(Food *foods)
{
	free(foods[0].tex);
	free(foods);
}


#endif  // FOOD