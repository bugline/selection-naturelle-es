#include "food.h"

#include "raymath.h"
#include "data.h"


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

void FoodMore()
{
	Data *data = DataPointer();
	data->nbFood *= 2;
	if (data->nbFood > FOOD_MAX)
		data->nbFood = FOOD_MAX;
	if (data->state == STATE_MENU)
		data->foods = FoodsInit(data->nbFood, &data->foodTex);
}

void FoodLess()
{
	Data *data = DataPointer();
	data->nbFood /= 2;
	if (data->nbFood < FOOD_MIN)
		data->nbFood = FOOD_MIN;
	if (data->state == STATE_MENU)
		data->foods = FoodsInit(data->nbFood, &data->foodTex);
}

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