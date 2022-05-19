#include "text.h"

#include <string.h>

#include "../../macros.h"


void UiButtText_init(UiButtText *pButt, Vector2 pPos, Vector2 pSize,
	char pAnch, const char *pText, int pFontSize, Color pCol,
	Color pFontCol, void (*pCallback) (void))
{
	UiButt_init(&pButt->mButt, pPos, pSize, pAnch, pCallback);
	pButt->mFontSize = pFontSize;
	pButt->mCol = pCol;
	pButt->mFontCol = pFontCol;

	size_t textLen = strlen(pText);
	pButt->mText = NEW_ARR(char, textLen);

	for (int i = 0; i < textLen; i++)
		pButt->mText[i] = pText[i];
	
	pButt->mTextSize = MeasureText(pButt->mText, pButt->mFontSize);
}

void UiButtText_update(UiButtText *pButt)
{
	UiButt_update(&pButt->mButt);
}

void UiButtText_render(const UiButtText *pButt)
{
	Vector2 topLeft = AnchGetRecTL(pButt->mButt.pos, pButt->mButt.size,
		pButt->mButt.anchor);
	DrawRectangleV(topLeft, pButt->mButt.size, pButt->mCol);

	Vector2 center = AnchGetRecC(pButt->mButt.pos, pButt->mButt.size,
		pButt->mButt.anchor);
	DrawText(pButt->mText, center.x - pButt->mTextSize / 2.f,
		center.y - pButt->mFontSize / 2.f, pButt->mFontSize,
		pButt->mFontCol);
}

void UiButtText_del(UiButtText *pButt)
{
	UiButt_del(&pButt->mButt);
	if (pButt->mText)
		free(pButt->mText);
}