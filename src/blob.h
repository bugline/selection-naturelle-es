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
	char score;
} Blob;


// Blobs
void BlobRender(const Blob *blob);

// Fonction pour simuler le choix du blob. Donne un vecteur de longueure 1.
Vector2 BlobGetDir(Vector2 pos, const Food *foods, int foodAmount);
void BlobTryEat(Blob *blob, Food *foods, int nbFood);


// Array of blobs
Blob *BlobsInit(int nbBlob);
void BlobsRender(const Blob *blobs, int nbBlob);
void BlobsDel(Blob *blobs);


// IMPLEMENTATION

void BlobRender(const Blob *blob)
{
	DrawCircleV(blob->pos, blob->size, blob->color);
}

Vector2 BlobGetDir(Vector2 pPos, const Food *pFoods, int pFoodLen)
{
	if (pFoodLen == 0)
		return (Vector2) { 0.f, 0.f };

	Vector2 closer = { 0.f, 0.f };
	float closerDist = 10e+10f;  // Considéré ici comme plus l'infini

	for (int i = 0; i < pFoodLen; i++) {
		if (!pFoods[i].eaten) {
			Vector2 foodPos = (Vector2) { pFoods[i].pos.x,
				pFoods[i].pos.y };
			Vector2 toVec = Vector2Subtract(foodPos, pPos);
			float dist = Vector2LengthSqr(toVec);

			if (dist < closerDist) {
				closer = toVec;
				closerDist = dist;
			}
		}
	}

	if (closerDist == 0.f)
		return (Vector2) { 0.f, 0.f };

	return Vector2Scale(closer, 1.f / sqrt(closerDist));
}

void BlobTryEat(Blob *pBlob, Food *pFoods, int pNbFood)
{
	for (int i = 0; i < pNbFood; i++) {
		if (!pFoods[i].eaten) {
			bool eating = FoodCircleColl(&pFoods[i], pBlob->pos,
				pBlob->size);
			if (eating) {
				pBlob->score += 1;
				pFoods[i].eaten = true;
			}
		}
	}
}

// Arrays

Blob *BlobsInit(int nbBlob)
{
	Blob *blobs = NEW_ARR(Blob, nbBlob);
	for (int i = 0; i < nbBlob; i++) {
		blobs[i].size = 1;
		float posX = GetRandomValue(-50, 50);
		float posY = GetRandomValue(-50, 50);
		blobs[i].pos = (Vector2) { posX, posY };
		blobs[i].color = (Color) { 255, 50, 50, 255 };
		blobs[i].score = 0;
	}
	return blobs;
}

void BlobsRender(const Blob *blobs, int nbBlob)
{
	for (int i = 0; i < nbBlob; i++) {
		BlobRender(&blobs[i]);
	}
}

void BlobsDel(Blob *blobs)
{
	free(blobs);
}


#endif  // BLOB