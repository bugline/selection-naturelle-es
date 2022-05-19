#ifndef GM_UI_BUTTON
#define GM_UI_BUTTON

#include "raylib.h"
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


#endif  // GM_UI_BUTTON