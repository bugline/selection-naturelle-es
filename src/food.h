#ifndef FOOD
#define FOOD

#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"
#include "gamemaker/core.h"
#include "linked_list.h"


// The foods default size
#define FOOD_DEF_SIZE ((Vector2) { 0.4f, 0.4f })


typedef struct Food {
	Vector2 pos;
	Vector2 size;
	Texture2D *tex;
} Food;


// DEFINITIONS

bool FoodCircleColl(const Food *food, const Vector2 circleCenter,
	const float radius);
void FoodRender(const Food *food);

// Arrays
LnList FoodsInit(int foodAmount, Texture2D *texture);
void FoodsRender(LnList *foods);
void FoodsDel(LnList *foods);


// IMPLEMENTATION

bool FoodCircleColl(const Food *pFood, const Vector2 pCircPos, const float pRad)
{
	float sqrdDist = Vector2LengthSqr(Vector2Subtract(pCircPos,
		pFood->pos));
	if (sqrdDist > pRad * pRad)
		return false;
	return true;
}

void FoodRender(const Food *food)
{
	DrawTexMid(*food->tex, food->pos, food->size);
}

// Array functions

LnList FoodsInit(int nbFood, Texture2D *tex)
{
	LnList foods = LnList_new(Food);

	for (int i = 0; i < nbFood; i++) {
		Food food;

		food.pos.x = GetRandomValue(-50, 50);
		food.pos.y = GetRandomValue(-50, 50);
		food.size = FOOD_DEF_SIZE;
		food.tex = tex;

		LnList_pushBack(Food, &foods, &food);
	}
	
	return foods;
}

/*Food *NewFood(Food *food, Food param)
{
	food = Push(food, sizeof(Food));
	Food *tmp = food->next;
	*food = param;
	food->next = tmp;
	return food;
}*/

void FoodsRender(LnList *foods)
{
	Iter iter = Iterate(foods);
	Food *food = Iter_getElem(Food, &iter);

	while (food != NULL) {
		FoodRender(food);

		Iter_next(&iter);
		food = Iter_getElem(Food, &iter);
	}
}

void FoodsDel(LnList *foods)
{
	LnList_clear(foods);
}


#endif  // FOOD