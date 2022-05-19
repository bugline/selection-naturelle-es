#ifndef GM_UI_PANEL
#define GM_UI_PANEL

#include "raylib.h"
#include "anchor.h"


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



#endif  // GM_UI_PANEL