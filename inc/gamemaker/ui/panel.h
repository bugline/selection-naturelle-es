#ifndef GM_UI_PANEL
#define GM_UI_PANEL

#include "raylib.h"
#include "anchor.h"
#include <string.h>


typedef struct UiPanel {
	Vector2 mPos;
	Vector2 mSize;
	char mAnch;
	Color mCol;
} UiPanel;


void UiPanel_init(UiPanel *panel, Vector2 position, Vector2 size, char anchor,
	Color color);
void UiPanel_render(const UiPanel *panel);
void UiPanel_del(UiPanel *panel);

// IMPLEMENTATION

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
	free(pPan);
}


#endif  // GM_UI_PANEL