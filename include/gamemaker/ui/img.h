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

// IMPLEMENTATION

void UiImg_init(UiImg *pImg, const char *pFName, Vector2 pPos, Vector2 pSize,
	char pAnch)
{
	pImg->mTex = LoadTexture(pFName);
	pImg->mPos = pPos;
	pImg->mSize = pSize;
	pImg->mAnch = pAnch;
}

void UiImg_render(const UiImg *pImg)
{
	Rectangle src = { 0.f, 0.f, pImg->mTex.width, pImg->mTex.height };
	Vector2 topLeft = AnchGetRecTL(pImg->mPos, pImg->mSize, pImg->mAnch);
	Rectangle dest = { topLeft.x, topLeft.y, pImg->mSize.x, pImg->mSize.y };
	DrawTexturePro(pImg->mTex, src, dest, Vector2Zero(), 0.f, WHITE);
}

void UiImg_del(UiImg *pImg)
{
	UnloadTexture(pImg->mTex);
}


#endif  // GM_UI_IMG