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


#endif  // FOOD