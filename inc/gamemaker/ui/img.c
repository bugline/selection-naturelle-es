#include "img.h"

#include "raymath.h"


void UiImg_init(UiImg *pImg, const char *pFName, Vector2 pPos, Vector2 pSize,
	char pAnch)
{
	pImg->mTex = LoadTexture(pFName);
	pImg->mPos = pPos;
	pImg->mSize = pSize;
	pImg->mAnch = pAnch;
}

/*------------------------------------------------------------------*/

void UiImg_render(const UiImg *pImg)
{
	Rectangle src = { 0.f, 0.f, pImg->mTex.width, pImg->mTex.height };
	Vector2 topLeft = AnchGetRecTL(pImg->mPos, pImg->mSize, pImg->mAnch);
	Rectangle dest = { topLeft.x, topLeft.y, pImg->mSize.x, pImg->mSize.y };
	DrawTexturePro(pImg->mTex, src, dest, Vector2Zero(), 0.f, WHITE);
}

/*------------------------------------------------------------------*/

void UiImg_del(UiImg *pImg)
{
	UnloadTexture(pImg->mTex);
}