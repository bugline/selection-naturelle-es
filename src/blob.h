#ifndef BLOB
#define BLOB

#include "gamemaker/core.h"
#include "raylib.h"
#include "raymath.h"

#include "food.h"


#define BLOB_MAX_SPEED 5.f
#define BLOB_MIN_SPEED .5f


typedef struct Blob {
	float size;
	Vector2 pos;
	Color color;
	int score;

	// Attributes
	float speed;
} Blob;


// Blobs
void BlobRender(const Blob *blob);

// Fonction pour simuler le choix du blob. Donne un vecteur de longueure 1.
Vector2 BlobGetDir(Vector2 pos, const Food *foods);
void BlobTryEat(Blob *blob, Food *foods);


// Array of blobs
Blob *BlobsInit(int nbBlob);
void BlobsRender(const Blob *blobs, int nbBlob);
void BlobsDel(Blob *blobs);


// IMPLEMENTATION

void BlobRender(const Blob *blob)
{
	DrawCircleV(blob->pos, blob->size, blob->color);
}

Vector2 BlobGetDir(Vector2 pPos, const Food *pFoods)
{
	Vector2 closer = { 0.f, 0.f };
	float closerDist = 10e+10f;  // Considéré ici comme plus l'infini
	
	while (pFoods) {
		if (!pFoods->eaten) {
			Vector2 foodPos = (Vector2) { pFoods->pos.x, pFoods->pos.y };
			Vector2 toVec = Vector2Subtract(foodPos, pPos);
			float dist = Vector2LengthSqr(toVec);

			if (dist < closerDist) {
				closer = toVec;
				closerDist = dist;
			}
		}
		pFoods = pFoods->next;
	}

	if (closerDist == 0.f)
		return (Vector2) { 0.f, 0.f };
	
	

	return Vector2Scale(closer, 1.f / sqrt(closerDist));
}

void BlobTryEat(Blob *pBlob, Food *pFoods)
{
	while (pFoods) {
		if (!pFoods->eaten) {
			bool eating = FoodCircleColl(pFoods, pBlob->pos,
				pBlob->size);
			if (eating) {
				pBlob->score += 1;
				printf("pop truc\n");
				Pop(pFoods, sizeof(Food));
				// pFoods->eaten = true;
				printf("fin pop tru\n");
				return;
			}
		}
		pFoods = pFoods->next;
	}
}

// Arrays

Vector2 GetRandBlobPos()
{
	return (Vector2) { GetRandomValue(-50, 50), GetRandomValue(-50, 50) };
}

void fclamp(float *val, float min, float max)
{
	if (*val > max)
		*val = max;
	if (*val < min)
		*val = min;
}

Blob BlobMutate(Blob blob)
{
	Blob newBlob = blob;

	newBlob.speed += (float) GetRandomValue(-100, 100) / 400.f;
	fclamp(&newBlob.speed, BLOB_MIN_SPEED, BLOB_MAX_SPEED);

	return newBlob;
}

Blob *BlobsInit(int nbBlob)
{
	Blob *blobs = NEW_ARR(Blob, nbBlob);
	for (int i = 0; i < nbBlob; i++) {
		blobs[i].size = 1;
		blobs[i].pos = GetRandBlobPos();
		blobs[i].color = (Color) { GetRandomValue(0, 255),
			GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
		blobs[i].score = 0;

		blobs[i].speed = GetRandomValue(BLOB_MIN_SPEED * 1e3f,
			(BLOB_MAX_SPEED - 3.f) * 1e3f) / 1e3f;
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