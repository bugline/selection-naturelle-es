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


void UiButtTex_init(UiButtTex *pButt, Vector2 pPos, Vector2 pSize, char pAnch,
	const char *pTex, void (*pCallback) (void))
{
	UiButt_init(&pButt->mButt, pPos, pSize, pAnch, pCallback);
	pButt->mTex = LoadTexture(pTex);
}

void UiButtTex_update(UiButtTex *pButt)
{
	UiButt_update(&pButt->mButt);
}

void UiButtTex_render(const UiButtTex *pButt)
{
	Rectangle src = { 0, 0, pButt->mTex.width, pButt->mTex.height };
	
	Vector2 topLeft = AnchGetRecTL(pButt->mButt.pos, pButt->mButt.size,
		pButt->mButt.anchor);
	Rectangle dest = { topLeft.x, topLeft.y, pButt->mButt.size.x,
		pButt->mButt.size.y };

	DrawTexturePro(pButt->mTex, src, dest, (Vector2) { 0.f, 0.f }, 0.f,
		WHITE);
}

void UiButtTex_del(UiButtTex *pButt)
{
	UiButt_del(&pButt->mButt);
	UnloadTexture(pButt->mTex);
	free(pButt);
}

#endif  // GM_UI_BUT_TEX