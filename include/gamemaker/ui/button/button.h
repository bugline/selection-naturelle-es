#ifndef GM_UI_BUTTON
#define GM_UI_BUTTON

#include <string.h>
#include <stdbool.h>
#include "raylib.h"
#include "../../macros.h"


typedef struct UiButton {
	Vector2 pos;   // de -1 à 1
	Vector2 size;  // de  0 à 1
	Color col;
	void (*callback) (void);
} UiButton;


void UiButInit(UiButton *button, Vector2 position, Vector2 size, Color color,
	void (*callback) (void));
void UiButUpdate(UiButton *button);
void UiButRender(UiButton *button);
void UiButDel(UiButton *button);


void UiButInit(UiButton *pButt, Vector2 pPos, Vector2 pSize, Color pCol,
	void (*pCallback) (void))
{
	pButt->pos = pPos;
	pButt->size = pSize;
	pButt->col = pCol;
	pButt->callback = pCallback;
}

static Vector2 GetPixPos(UiButton *pButt)
{
	return (Vector2) {
		GetScreenWidth() / 2.f * (1 + pButt->pos.x),
		GetScreenHeight() / 2.f * (1 + pButt->pos.y) 
	};
}

static Vector2 GetPixSize(UiButton *pButt)
{
	return (Vector2) {
		GetScreenWidth() * pButt->size.x,
		GetScreenHeight() * pButt->size.y
	};
}

static Vector2 GetPixTopLeftPos(UiButton *pButt)
{
Vector2 pos = GetPixPos(pButt);

	return (Vector2) {
		pos.x - GetScreenWidth() / 2.f * pButt->size.x,
		pos.y - GetScreenHeight() / 2.f * pButt->size.y
	};
}

static Vector2 GetPixBotRightPos(UiButton *pButt)
{
	Vector2 pos = GetPixPos(pButt);

	return (Vector2) {
		pos.x + GetScreenWidth() / 2.f * pButt->size.x,
		pos.y + GetScreenHeight() / 2.f * pButt->size.y
	};
}

static bool CheckCollision(UiButton *pButt)
{
	Vector2 topLeft = GetPixTopLeftPos(pButt);
	Vector2 botRight = GetPixBotRightPos(pButt);

	if (topLeft.x > GetMouseX() || botRight.x < GetMouseX() ||
		topLeft.y > GetMouseY() || botRight.y < GetMouseY())
		return false;

	return true;
}

void UiButUpdate(UiButton *pButt)
{
	if (IsMouseButtonPressed(0) && pButt->callback) {
		if (CheckCollision(pButt))
			pButt->callback();
	}
}

void UiButRender(UiButton *pButt)
{
	DrawRectangleV(GetPixTopLeftPos(pButt), GetPixSize(pButt), pButt->col);
}

void UiButDel(UiButton *pButt)
{
}


#endif  // GM_UI_BUTTON