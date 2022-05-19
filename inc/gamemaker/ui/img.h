#ifndef GM_UI_IMG
#define GM_UI_IMG

#include "raylib.h"
#include "anchor.h"


typedef struct UiImg {
	Texture2D mTex;
	Vector2 mPos;
	Vector2 mSize;
	char mAnch;
} UiImg;


void UiImg_init(UiImg *image, const char *fileName, Vector2 position,
	Vector2 size, char anchor);
void UiImg_render(const UiImg *image);
void UiImg_del(UiImg *image);


#endif  // GM_UI_IMG