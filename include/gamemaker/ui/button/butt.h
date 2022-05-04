#ifndef GM_UI_BUTTON
#define GM_UI_BUTTON

#include <string.h>
#include <stdbool.h>
#include "raylib.h"
#include "../../macros.h"
#include "../anchor.h"


typedef struct UiButt {
	Vector2 pos;
	Vector2 size;
	char anchor;
	void (*callback) (void);
} UiButt;


void UiButt_init(UiButt *button, Vector2 position, Vector2 size, char anchor,
	void (*callback) (void));
void UiButt_update(UiButt *button);
void UiButt_del(UiButt *button);


// IMPLEMENTATION
void UiButt_init(UiButt *pButt, Vector2 pPos, Vector2 pSize, char pAnch,
	void (*pCallback) (void))
{
	pButt->pos = pPos;
	pButt->size = pSize;
	pButt->anchor = pAnch;
	pButt->callback = pCallback;
}

bool CheckCollision(UiButt *pButt)
{
	Vector2 topLeft = AnchGetRecTL(pButt->pos, pButt->size, pButt->anchor);
	Vector2 bottomRight = AnchGetRecBR(pButt->pos, pButt->size, pButt->anchor);
	Vector2 mp = GetMousePosition();

	if (mp.x < topLeft.x || mp.x > bottomRight.x || mp.y < topLeft.y ||
			mp.y > bottomRight.y) {
		return false;
	}

	return true;
}

void UiButt_update(UiButt *pButt)
{
	if (IsMouseButtonPressed(0) && pButt->callback) {
		if (CheckCollision(pButt))
			pButt->callback();
	}
}

void UiButt_del(UiButt *pButt)
{
}


#endif  // GM_UI_BUTTON