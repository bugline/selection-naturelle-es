#include "butt.h"

#include <string.h>
#include <stdbool.h>

#include "../../macros.h"


void UiButt_init(UiButt *pButt, Vector2 pPos, Vector2 pSize, char pAnch,
	void (*pCallback) (void))
{
	pButt->pos = pPos;
	pButt->size = pSize;
	pButt->anchor = pAnch;
	pButt->callback = pCallback;
}

/*------------------------------------------------------------------*/

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

/*------------------------------------------------------------------*/

void UiButt_update(UiButt *pButt)
{
	if (IsMouseButtonPressed(0) && pButt->callback) {
		if (CheckCollision(pButt))
			pButt->callback();
	}
}

/*------------------------------------------------------------------*/

void UiButt_del(UiButt *pButt)
{
}