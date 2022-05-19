#include "panel.h"
#include <string.h>


void UiPanel_init(UiPanel *pPan, Vector2 pPos, Vector2 pSize, char pAnch,
	Color pCol)
{
	pPan->mPos = pPos;
	pPan->mSize = pSize;
	pPan->mAnch = pAnch;
	pPan->mCol = pCol;
}

void UiPanel_render(const UiPanel *pPan)
{
	Vector2 topLeft = AnchGetRecTL(pPan->mPos, pPan->mSize, pPan->mAnch);
	DrawRectangleV(topLeft, pPan->mSize, pPan->mCol);
}

void UiPanel_del(UiPanel *pPan)
{
}