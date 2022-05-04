#include "raylib.h"

#ifndef GM_DRAW_H
#define GM_DRAW_H

typedef struct Frame {  // Pourquoi ? Les vecteurs éxistent déjà
	int x;
	int y;
} Frame;


void DrawRecMid(Vector2 position, Vector2 size, Color color);
void DrawTexMid(Texture texture, Vector2 position, Vector2 size);
void DrawFrameMid(Texture tileMap, Vector2 position, Vector2 size,
	Frame tileAmount, Frame framePosition);
void DrawArcMid(Vector2 position, float radius, float startAngle,
	float stopAngle, int lines, Color color);


void DrawRecMid(Vector2 pPos, Vector2 pSize, Color pCol)
{
	Vector2 pos = { pPos.x - pSize.x / 2.f, pPos.y - pSize.y / 2.f };
	DrawRectangleV(pos, pSize, pCol);
}

void DrawTexMid(Texture tex, Vector2 pos, Vector2 size)
{
	Rectangle source = { 0, 0, tex.width, tex.height };

	float width = tex.width / 100.f * size.x;
	float height = tex.height / 100.f * size.y;

	Rectangle dest = { -width / 2 + pos.x, -height / 2 + pos.y,
		width, height };

	DrawTexturePro(tex, source, dest, (Vector2) { 0.f, 0.f }, 0.f, WHITE);
}

void DrawFrameMid(Texture tex, Vector2 pos, Vector2 size, Frame nbFrame,
	Frame posFrame)
{
	int widthFrame = tex.width / nbFrame.x;
	int heightFrame = tex.height / nbFrame.y;
	Rectangle frameRec = { widthFrame * posFrame.x,
		heightFrame * posFrame.y, widthFrame, heightFrame };

	float width = widthFrame / 100.f * size.x;
	float height = heightFrame / 100.f * size.y;

	Rectangle dest = { -width / 2 + pos.x, -height / 2 + pos.y,
		width, height };

	DrawTexturePro(tex, frameRec, dest, (Vector2) { 0.f, 0.f }, 0.f,
		WHITE);
}

void DrawArcMid(Vector2 pPos, float pRad, float pStartAngle, float pStopAngle,
	int pLines, Color pCol)
{
	DrawCircleSector(pPos, pRad, pStartAngle, pStopAngle, pLines, pCol);
}

#endif // GM_DRAW_H