#ifndef BLOB
#define BLOB

#include <stdbool.h>

#include "gamemaker/core.h"
#include "raylib.h"
#include "raymath.h"
#include "linked_list.h"

#include "food.h"


#define BLOB_MAX_SPEED  5.f
#define BLOB_MIN_SPEED  .5f
#define BLOB_ENERGY     30.f


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
void BlobMore(int *nbBlob, LnList *blobs);
void BlobLess(int *nbBlob, LnList *blobs);
bool BlobsStillHaveEnergy(LnList *blobs);
void BlobsRender(LnList *blobs);
void BlobsDel(LnList *blobs);

#endif  // BLOB