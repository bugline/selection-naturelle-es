#ifndef GM_UI_BUT_TEX
#define GM_UI_BUT_TEX

#include "raylib.h"
#include "butt.h"


typedef struct UiButtTex {
	UiButt mButt;
	Texture2D mTex;
} UiButtTex;


void UiButtTex_init(UiButtTex *button, Vector2 position, Vector2 size,
	char anchor, const char *texture, void (*callback) (void));
void UiButtTex_update(UiButtTex *button);
void UiButtTex_render(const UiButtTex *button);
void UiButtTex_del(UiButtTex *button);


#endif  // GM_UI_BUT_TEX