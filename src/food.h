#ifndef FOOD
#define FOOD

#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"
#include "gamemaker/core.h"


typedef struct Food {
	struct Food *next;
	Vector2 pos;
	Vector2 size;
	Texture2D *tex;
	bool eaten;
	
} Food;

void *NewLinkedList(int size, size_t typeSize) {
	void *first = malloc(typeSize);
	void **prec = first;
	void *curr;
	for (int i = 1; i < size; i++) {
		curr = malloc(typeSize);
		*prec = curr;
		prec = curr;
	}
	*prec = NULL;

	return first;
}


bool FoodCircleColl(const Food *food, const Vector2 circleCenter,
	const float radius);
void FoodDraw(const Food *food);

// Arrays
Food *FoodsInit(int nbFood);
void FoodsRender(Food *foods);
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
	Food *foods = NewLinkedList(nbFood, sizeof(Food));
	Food *first = foods;

	Texture2D *tex = NEW(Texture2D);
	*tex = LoadTexture("res/food.png");
	float width = 0.4f;
	float height = 0.4f;

	while (foods) {
		foods->pos.x = GetRandomValue(-50, 50);
		foods->pos.y = GetRandomValue(-50, 50);
		foods->size = (Vector2) { width, height };
		foods->tex = tex;
		foods->eaten = false;
		foods = foods->next;
	}
	
	return first;
}

void FoodsRender(Food *foods)
{
	while (foods) {
		if (!foods->eaten) {
			FoodDraw(foods);
		}
		foods = foods->next;
	}
}

void FoodsDel(Food *foods)
{
	free(foods->tex);
	while (foods) {
		Food *prec = foods;
		foods = foods->next;
		free(prec);
	}
}


#endif  // FOOD