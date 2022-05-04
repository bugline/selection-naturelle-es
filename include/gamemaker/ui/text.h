#ifndef GM_UI_TEXT
#define GM_UI_TEXT

#include "raylib.h"
#include "anchor.h"
#include <string.h>


typedef struct UiText {
	char *mText;
	Font mFont;
	Vector2 mPos;
	Vector2 mSize;
	char mAnch;
	float mSpacing;
	Color mCol;
} UiText;


void UiText_init(UiText *uitext, const char *text, Font font, float fontSize,
	Vector2 position, char anchor, Color color);
void UiText_render(const UiText *text);
void UiText_del(UiText *text);

// IMPLEMENTATION

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
	pUiText->mText = (char *) malloc(textLen);

	for (int i = 0; i < textLen; i++)
		pUiText->mText[i] = pText[i];
}

void UiText_render(const UiText *pText)
{
	Vector2 pos = AnchGetRecTL(pText->mPos, pText->mSize, pText->mAnch);
	DrawTextEx(pText->mFont, pText->mText, pos, pText->mSize.y,
		pText->mSpacing, pText->mCol);
}

void UiText_del(UiText *pText)
{
	free(pText->mText);
}


#endif  // GM_UI_TEXT