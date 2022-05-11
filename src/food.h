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

void *Push(void *first, size_t typeSize)
{
	void **new = malloc(typeSize);
	*new = first;
	return new;
}

void ListCopy(void *dest, void *src, const size_t typeSize)
{
	for (size_t i = 0; i < typeSize; i++) {
		((char *) dest)[i] = ((const char *) src)[i];
	}
}

bool FoodCircleColl(const Food *food, const Vector2 circleCenter,
	const float radius);
void FoodDraw(const Food *food);

// Arrays
Food *FoodsInit(int foodAmount, Texture2D *texture);
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

bool AreAllFoodsGone(Food *food)
{
	while (food) {
		if (!food->eaten)
			return false;
		food = food->next;
	}
	return true;
}

void FoodDraw(const Food *food)
{
	DrawTexMid(*food->tex, food->pos, food->size);
}

// Array functions

Food *FoodsInit(int nbFood, Texture2D *tex)
{
	Food *foods = NewLinkedList(nbFood, sizeof(Food));
	Food *first = foods;

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

Food *NewFood(Food *food, Food param)
{
	food = Push(food, sizeof(Food));
	Food *tmp = food->next;
	*food = param;
	food->next = tmp;
	return food;
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
	while (foods) {
		Food *prec = foods;
		foods = foods->next;
		free(prec);
	}
}


#endif  // FOOD