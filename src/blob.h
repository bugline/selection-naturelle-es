#ifndef BLOB
#define BLOB

#include <stdbool.h>

#include "gamemaker/core.h"
#include "raylib.h"
#include "raymath.h"
#include "linked_list.h"

#include "food.h"


#define BLOB_MAX_SPEED  5.f
#define BLOB_SPEED_MUTATION 0.0003f
#define BLOB_MIN_SPEED  .5f
#define BLOB_ENERGY     100.f
#define BLOB_MAX 10000
#define BLOB_MIN 1


typedef struct Blob {
	float size;
	Vector2 pos;
	Color color;
	int score;

	// Attributes
	float speed;
	float energy;
} Blob;


// Blob
void BlobRender(const Blob *blob);

// Fonction pour simuler le choix du blob. Donne un vecteur de longueure 1.
Vector2 BlobGetDir(Vector2 pos, LnList *foods);
void BlobTryEat(Blob *blob, LnList *foods);

Vector2 GetRandBlobPos(void);
Blob BlobMutate(Blob blob);

// Array of blobs
LnList BlobsInit(int nbBlob);
bool BlobsStillHaveEnergy(LnList *blobs);
void BlobMore();
void BlobLess();
void BlobsRender(LnList *blobs);
void BlobsDel(LnList *blobs);

#endif  // BLOB