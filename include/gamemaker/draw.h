#include "raylib.h"

#ifndef GM_DRAW_H
#define GM_DRAW_H

typedef struct Frame {
	int x;
	int y;
} Frame;

void DrawRecMid(Vector2 pos, Vector2 size)
{
	pos.x -= size.x / 2;
	pos.y -= size.y / 2;
	DrawRectangleV(pos, size, (Color) { 255, 255, 255, 255 });
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

void DrawFrameMid(Texture tex, Vector2 pos, Vector2 size, Frame nbFrame, Frame posFrame)
{
	int widthFrame = tex.width / nbFrame.x;
	int heightFrame = tex.height / nbFrame.y;
	Rectangle frameRec = { widthFrame * posFrame.x, heightFrame * posFrame.y, widthFrame, heightFrame };

	float width = widthFrame / 100.f * size.x;
	float height = heightFrame / 100.f * size.y;

	Rectangle dest = { -width / 2 + pos.x, -height / 2 + pos.y, width, height };

	DrawTexturePro(tex, frameRec, dest, (Vector2) { 0.f, 0.f }, 0.f, WHITE);
}

#endif // GM_DRAW_H