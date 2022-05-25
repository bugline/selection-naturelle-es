#include "anchor.h"
#include "raymath.h"
 

Vector2 AnchGetOrig(char pAnch)
{
	Vector2 origin;

	if (pAnch == ANCHOR_NW) {
		origin = (Vector2) { 0.f, 0.f };
	} else if (pAnch == ANCHOR_NE) {
		origin = (Vector2) { (float) GetScreenWidth(), 0.f };
	} else if (pAnch == ANCHOR_SW) {
		origin = (Vector2) { 0.f, (float) GetScreenHeight() };
	} else if (pAnch == ANCHOR_SE) {
		origin = (Vector2) { (float) GetScreenWidth(), (float) GetScreenHeight() };
	} else if (pAnch == ANCHOR_C) {
		origin = (Vector2) { (float) GetScreenWidth() / 2.f, (float) GetScreenHeight() / 2.f };
	} else if (pAnch == ANCHOR_W) {
		origin = (Vector2) { 0.f, (float) GetScreenHeight() / 2.f };
	} else if (pAnch == ANCHOR_N) {
		origin = (Vector2) { (float) GetScreenWidth() / 2.f, 0.f };
	} else if (pAnch == ANCHOR_E) {
		origin = (Vector2) { (float) GetScreenWidth(), (float) GetScreenHeight() / 2.f };
	} else if (pAnch == ANCHOR_S) {
		origin = (Vector2) { (float) GetScreenWidth() / 2.f, (float) GetScreenHeight()};
	} else {
		origin = (Vector2) { 0.f, 0.f };
	}

	return origin;
}

/*------------------------------------------------------------------*/

Vector2 AnchGetRecC(Vector2 pPos, Vector2 pSize, char pAnch)
{
	Vector2 origin = (Vector2) AnchGetOrig(pAnch);
	Vector2 pos = Vector2Add(origin, pPos);

	Vector2 res;

	if (pAnch == ANCHOR_NW) {
		res = (Vector2) { pos.x + pSize.x / 2.f, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_NE) {
		res = (Vector2) { pos.x - pSize.x / 2.f, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_SW) {
		res = (Vector2) { pos.x + pSize.x / 2.f, pos.y - pSize.y / 2.f };
	} else if (pAnch == ANCHOR_SE) {
		res = (Vector2) { pos.x - pSize.x / 2.f, pos.y - pSize.y / 2.f };
	} else if (pAnch == ANCHOR_C) {
		res = (Vector2) pos;
	} else if (pAnch == ANCHOR_W) {
		res = (Vector2) { pos.x + pSize.x / 2.f, pos.y };
	} else if (pAnch == ANCHOR_N) {
		res = (Vector2) { pos.x, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_E) {
		res = (Vector2) { pos.x - pSize.x / 2.f, pos.y };
	} else if (pAnch == ANCHOR_S) {
		res = (Vector2) { pos.x, pos.y - pSize.y / 2.f };
	} else {
		res = (Vector2) { 0.f, 0.f };
	}

	return res;
}

/*------------------------------------------------------------------*/

Vector2 AnchGetRecTL(Vector2 pPos, Vector2 pSize, char pAnch)
{
	Vector2 origin = (Vector2) AnchGetOrig(pAnch);
	Vector2 pos = Vector2Add(origin, pPos);

	Vector2 res;

	if (pAnch == ANCHOR_NW) {
		res = (Vector2) pos;
	} else if (pAnch == ANCHOR_NE) {
		res = (Vector2) { pos.x - pSize.x, pos.y };
	} else if (pAnch == ANCHOR_SW) {
		res = (Vector2) { pos.x, pos.y - pSize.y };
	} else if (pAnch == ANCHOR_SE) {
		res = (Vector2) { pos.x - pSize.x, pos.y - pSize.y };
	} else if (pAnch == ANCHOR_C) {
		res = (Vector2) { pos.x - pSize.x / 2.f, pos.y - pSize.y / 2.f };
	} else if (pAnch == ANCHOR_W) {
		res = (Vector2) { pos.x, pos.y - pSize.y / 2.f };
	} else if (pAnch == ANCHOR_N) {
		res = (Vector2) {pos.x - pSize.x / 2.f , pos.y };
	} else if (pAnch == ANCHOR_E) {
		res = (Vector2) { pos.x - pSize.x, pos.y - pSize.y / 2.f };
	} else if (pAnch == ANCHOR_S) {
		res = (Vector2) { pos.x - pSize.x / 2.f, pos.y - pSize.y };
	} else {
		res = (Vector2) { 0.f, 0.f };
	}

	return res;
}

/*------------------------------------------------------------------*/

Vector2 AnchGetRecTR(Vector2 pPos, Vector2 pSize, char pAnch)
{
	Vector2 origin = (Vector2) AnchGetOrig(pAnch);
	Vector2 pos = Vector2Add(origin, pPos);

	Vector2 res;

	if (pAnch == ANCHOR_NW) {
		res = (Vector2)  { pos.x + pSize.x, pos.y};
	} else if (pAnch == ANCHOR_NE) {
		res = (Vector2) pos;
	} else if (pAnch == ANCHOR_SW) {
		res = (Vector2) { pos.x + pSize.x, pos.y - pSize.y };
	} else if (pAnch == ANCHOR_SE) {
		res = (Vector2) { pos.x, pos.y - pSize.y };
	} else if (pAnch == ANCHOR_C) {
		res = (Vector2) { pos.x + pSize.x / 2.f, pos.y - pSize.y / 2.f };
	} else if (pAnch == ANCHOR_W) {
		res = (Vector2) { pos.x + pSize.x, pos.y - pSize.y / 2.f };
	} else if (pAnch == ANCHOR_N) {
		res = (Vector2) { pos.x + pSize.x / 2.f, pos.y };
	} else if (pAnch == ANCHOR_E) {
		res = (Vector2) { pos.x, pos.y - pSize.y / 2.f };
	} else if (pAnch == ANCHOR_S) {
		res = (Vector2) { pos.x + pSize.x / 2.f, pos.y - pSize.y };
	} else {
		res = (Vector2) { 0.f, 0.f };
	}

	return res;
}

/*------------------------------------------------------------------*/

Vector2 AnchGetRecBL(Vector2 pPos, Vector2 pSize, char pAnch)
{
	Vector2 origin = (Vector2) AnchGetOrig(pAnch);
	Vector2 pos = Vector2Add(origin, pPos);

	Vector2 res;

	if (pAnch == ANCHOR_NW) {
		res = (Vector2) { pos.x, pos.y + pSize.y };
	} else if (pAnch == ANCHOR_NE) {
		res = (Vector2) { pos.x - pSize.x, pos.y + pSize.y };
	} else if (pAnch == ANCHOR_SW) {
		res = (Vector2) { pos.x, pos.y };
	} else if (pAnch == ANCHOR_SE) {
		res = (Vector2) { pos.x - pSize.x, pos.y };
	} else if (pAnch == ANCHOR_C) {
		res = (Vector2) { pos.x - pSize.x / 2.f, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_W) {
		res = (Vector2) { pos.x, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_N) {
		res = (Vector2) {pos.x - pSize.x / 2.f , pos.y + pSize.y };
	} else if (pAnch == ANCHOR_E) {
		res = (Vector2) { pos.x - pSize.x, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_S) {
		res = (Vector2) { pos.x - pSize.x / 2.f, pos.y };
	} else {
		res = (Vector2) { 0.f, 0.f };
	}

	return res;
}

/*------------------------------------------------------------------*/

Vector2 AnchGetRecBR(Vector2 pPos, Vector2 pSize, char pAnch)
{
	Vector2 origin = (Vector2) AnchGetOrig(pAnch);
	Vector2 pos = Vector2Add(origin, pPos);

	Vector2 res;

	if (pAnch == ANCHOR_NW) {
		res = (Vector2) Vector2Add(pos, pSize);
	} else if (pAnch == ANCHOR_NE) {
		res = (Vector2) { pos.x, pos.y + pSize.y };
	} else if (pAnch == ANCHOR_SW) {
		res = (Vector2) { pos.x + pSize.x, pos.y };
	} else if (pAnch == ANCHOR_SE) {
		res = (Vector2) pos;
	} else if (pAnch == ANCHOR_C) {
		res = (Vector2) { pos.x + pSize.x / 2.f, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_W) {
		res = (Vector2) { pos.x + pSize.x, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_N) {
		res = (Vector2) {pos.x + pSize.x / 2.f, pos.y + pSize.y };
	} else if (pAnch == ANCHOR_E) {
		res = (Vector2) { pos.x, pos.y + pSize.y / 2.f };
	} else if (pAnch == ANCHOR_S) {
		res = (Vector2) { pos.x + pSize.x / 2.f, pos.y };
	} else {
		res = (Vector2) { 0.f, 0.f };
	}

	return res;
}