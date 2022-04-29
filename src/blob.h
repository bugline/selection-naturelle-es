#ifndef BLOB
#define BLOB

#include "gamemaker/core.h"
#include "raylib.h"


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


#endif  // BLOB