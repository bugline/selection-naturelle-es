#ifndef GM_DRAW_H
#define GM_DRAW_H

#include "raylib.h"

typedef struct Frame {  // Pourquoi ? Les vecteurs éxistent déjà
	int x;
	int y;
} Frame;


void DrawRecMid(Vector2 position, Vector2 size, Color color);
void DrawTexMid(Texture2D texture, Vector2 position, Vector2 size);
void DrawFrameMid(Texture2D tileMap, Vector2 position, Vector2 size,
	Frame tileAmount, Frame framePosition);
void DrawArcMid(Vector2 position, float radius, float startAngle,
	float stopAngle, int lines, Color color);


#endif // GM_DRAW_H