#include "tex.h"


void UiButtTex_init(UiButtTex *pButt, Vector2 pPos, Vector2 pSize, char pAnch,
	const char *pTex, void (*pCallback) (void))
{
	UiButt_init(&pButt->mButt, pPos, pSize, pAnch, pCallback);
	pButt->mTex = LoadTexture(pTex);
	pButt->color = WHITE;
}

/*------------------------------------------------------------------*/

void UiButtTex_update(UiButtTex *pButt)
{
	UiButt_update(&pButt->mButt);
}

/*------------------------------------------------------------------*/

void UiButtTex_render(const UiButtTex *pButt)
{
	Rectangle src = { 0, 0, pButt->mTex.width, pButt->mTex.height };
	
	Vector2 topLeft = AnchGetRecTL(pButt->mButt.pos, pButt->mButt.size,
		pButt->mButt.anchor);
	Rectangle dest = { topLeft.x, topLeft.y, pButt->mButt.size.x,
		pButt->mButt.size.y };

	DrawTexturePro(pButt->mTex, src, dest, (Vector2) { 0.f, 0.f }, 0.f,
		pButt->color);
}

/*------------------------------------------------------------------*/

void UiButtTex_del(UiButtTex *pButt)
{
	UiButt_del(&pButt->mButt);
	UnloadTexture(pButt->mTex);
}