/*
#ifndef BLOB
#define BLOB

#include "gamemaker/core.h"
#include "raylib.h"
#include "raymath.h"

#include "food.h"


typedef struct Blob {
	float size;
	Vector2 pos;
	Color color;
} Blob;


// Blobs
void BlobRender(const Blob *blob);


// Array of blobs
Blob *BlobsInit(int nbBlob);
void BlobsRender(const Blob *blobs, int nbBlob);

// Fonction pour simuler le choix du blob. Donne un vecteur de longueure 1.
Vector2 BlobGetDir(Vector2 pos, const Food *foods, int foodAmount);


// IMPLEMENTATION

void BlobRender(const Blob *blob)
{
	DrawCircle(blob->pos.x, blob->pos.y, blob->size, blob->color);
}


// ARRAYS

Blob *BlobsInit(int nbBlob)
{
	Blob *blobs = NEW_ARR(Blob, nbBlob);
	for (int i = 0; i < nbBlob; i++) {
		blobs[i].size = 5;
		float posX = GetRandomValue(-50, 50);
		float posY = GetRandomValue(-50, 50);
		blobs[i].pos = (Vector2) { posX, posY };
		blobs[i].color = (Color) { 255, 50, 50, 255 };
	}
	return blobs;
}

void BlobsRender(const Blob *blobs, int nbBlob)
{
	for (int i = 0; i < nbBlob; i++) {
		BlobRender(&(blobs[i]));
	}
}


Vector2 BlobGetDir(Vector2 pPos, const Food *pFoods, int pFoodLen)
{
	if (pFoodLen == 0)
		return (Vector2) { 0.f, 0.f };

	Vector2 closer = Vector2Subtract(pFoods[0].pos, pPos);
	float closerDist = Vector2LengthSqr(closer);

	for (int i = 1; i < pFoodLen; i++) {
		Vector2 toVec = Vector2Subtract(pFoods[i].pos, pPos);
		float dist = Vector2LengthSqr(toVec);

		if (dist < closerDist) {
			closer = toVec;
			closerDist = dist;
		}
	}

	if (closerDist = 0.f)
		return (Vector2) { 0.f, 0.f };
	
	return Vector2Scale(closer, 1.f / sqrt(closerDist));
}


#endif  // BLOB */