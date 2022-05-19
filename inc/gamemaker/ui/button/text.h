#ifndef GM_UI_BUT_TEXT
#define GM_UI_BUT_TEXT

#include "raylib.h"
#include "butt.h"


typedef struct UiButtText {
	UiButt mButt;
	char *mText;
	int mTextSize;
	int mFontSize;
	Color mCol;
	Color mFontCol;
} UiButtText;


void UiButtText_init(UiButtText *button, Vector2 position, Vector2 size,
	char anchor, const char *text, int fontSize, Color color,
	Color fontColor, void (*callback) (void));
void UiButtText_update(UiButtText *button);
void UiButtText_render(const UiButtText *button);
void UiButtText_del(UiButtText *button);


#endif  // GM_UI_BUT_TEXT