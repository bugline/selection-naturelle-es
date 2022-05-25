#ifndef GM_UI_TEXT
#define GM_UI_TEXT

#include "raylib.h"
#include "anchor.h"

//Stockage des informations nessécaire a un message écrit
typedef struct UiText {
	char *mText;
	Font mFont;
	Vector2 mPos;
	Vector2 mSize;
	char mAnch;
	float mSpacing;
	Color mCol;
} UiText;

//initialise les valeur du texte(taille, message...)
void UiText_init(UiText *uitext, const char *text, Font font, float fontSize,
	Vector2 position, char anchor, Color color);
void UiText_chngTxt(UiText *uiText, const char *newText);
//écrit le texte
void UiText_render(const UiText *text);
//suprimr le texte
void UiText_del(UiText *text);


#endif  // GM_UI_TEXT