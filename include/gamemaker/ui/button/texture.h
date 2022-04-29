#ifndef GM_UI_BUT_TEX
#define GM_UI_BUT_TEX

#include "button.h"


typedef struct UiButtTex {
	UiButton mButt;
	Texture2D mTex;
} UiButtTex;


void UiButTexInit(UiButtTex *button, Vector2 position, float size,
	const char *texture, void (*callback) (void));
void UiButTexUpdate(UiButtTex *button);
void UiButTexRender(UiButtTex *button);
void UiButTexDel(UiButtTex *button);


void UiButTexInit(UiButtTex *pButt, Vector2 pPos, float pSize, const char *pTex,
	void (*pCallback) (void))
{
	pButt->mButt.pos = pPos;
	pButt->mTex = LoadTexture(pTex);

	pButt->mButt.size = (Vector2) { pSize, pSize * pButt->mTex.height /
		pButt->mTex.width *  GetScreenWidth() / GetScreenHeight() };
	
	pButt->mButt.callback = pCallback;
}

void UiButTexUpdate(UiButtTex *pButt)
{
	UiButUpdate(&(pButt->mButt));
}

void UiButTexRender(UiButtTex *pButt)
{
	Rectangle src = { 0, 0, pButt->mTex.width, pButt->mTex.height };
	
	Vector2 topLeft = GetPixTopLeftPos(&(pButt->mButt));
	Vector2 size = GetPixSize(&(pButt->mButt));
	Rectangle dest = { topLeft.x, topLeft.y, size.x, size.y };

	DrawTexturePro(pButt->mTex, src, dest, (Vector2) { 0.f, 0.f }, 0.f,
		WHITE);
}

void UiButTexDel(UiButtTex *pButt)
{
	UiButDel(&(pButt->mButt));
	UnloadTexture(pButt->mTex);
}

#endif  // GM_UI_BUT_TEX