#include "text.h"

#include <string.h>

#include "../macros.h"


void UiText_init(UiText *pUiText, const char *pText, Font pFont,
	float pFontSize, Vector2 pPos, char pAnch, Color pCol)
{
	pUiText->mFont = pFont;
	pUiText->mPos = pPos;
	pUiText->mAnch = pAnch;
	pUiText->mSpacing = pFontSize / 10.f;
	pUiText->mCol = pCol;

	pUiText->mSize = MeasureTextEx(pFont, pText, pFontSize,
		pFontSize / 10.f);

	size_t textLen = strlen(pText);
	pUiText->mText = NEW_ARR(char, textLen);

	for (int i = 0; i < textLen; i++)
		pUiText->mText[i] = pText[i];
}

void UiText_chngTxt(UiText *uiText, const char *newText)
{
	if (uiText->mText)
		free(uiText->mText);
	
	uiText->mSize = MeasureTextEx(uiText->mFont, newText, uiText->mSize.y,
		uiText->mSpacing);

	size_t textLen = strlen(newText);
	uiText->mText = (char *) malloc(textLen);
	if (uiText->mText)
		strcpy(uiText->mText, newText);
}

void UiText_render(const UiText *pText)
{
	Vector2 pos = AnchGetRecTL(pText->mPos, pText->mSize, pText->mAnch);
	DrawTextEx(pText->mFont, pText->mText, pos, pText->mSize.y,
		pText->mSpacing, pText->mCol);
}

void UiText_del(UiText *pText)
{
	if (pText->mText) {
		free(pText->mText);
	}
}