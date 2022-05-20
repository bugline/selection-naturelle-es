#include "blob.h"
#include "data.h"

void BlobRender(const Blob *blob)
{
	DrawCircleV(blob->pos, blob->size, blob->color);
}

Vector2 BlobGetDir(Vector2 pPos, LnList *pFoods)
{
	Vector2 closer = { 0.f, 0.f };
	float closerDist = 10e+10f;  // Considéré ici comme plus l'infini

	Iter iter = Iterate(pFoods);
	Food *food = Iter_getElem(Food, &iter);

	while (food != NULL) {
		Vector2 toVec = Vector2Subtract(food->pos, pPos);
		float dist = Vector2LengthSqr(toVec);

		if (dist < closerDist) {
			closer = toVec;
			closerDist = dist;
		}

		Iter_next(&iter);
		food = Iter_getElem(Food, &iter);
	}

	if (closerDist == 0.f)
		return (Vector2) { 0.f, 0.f };

	return Vector2Scale(closer, 1.f / sqrt(closerDist));
}

void BlobTryEat(Blob *pBlob, LnList *pFoods)
{
	Iter iter = Iterate(pFoods);
	Food *food = Iter_getElem(Food, &iter);

	while (food != NULL) {
		bool eating = FoodCircleColl(food, pBlob->pos, pBlob->size);

		Food *prevFood = food;
		Iter_next(&iter);
		food = Iter_getElem(Food, &iter);

		if (eating) {
			pBlob->score++;
			LnList_rem(pFoods, prevFood);
		}
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

LnList BlobsInit(int nbBlob)
{
	LnList blobs = LnList_new(Blob);

	for (int i = 0; i < nbBlob; i++) {
		Blob blob;

		blob.pos = GetRandBlobPos();
		blob.size = 1;

		blob.color = (Color) { GetRandomValue(0, 255),
			GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };

		blob.score = 0;

		blob.speed = GetRandomValue(BLOB_MIN_SPEED * 1e3f,
			(BLOB_MAX_SPEED - 3.f) * 1e3f) / 1e3f;
		
		LnList_pushBack(Blob, &blobs, &blob);
	}

	return blobs;
}

void BlobMore()
{
	Data *data = DataPointer();
	data->nbBlob *= 2;
	if (data->nbBlob > BLOB_MAX)
        	data->nbBlob = BLOB_MAX;
    	if (data->blobs.first != NULL)
		BlobsDel(&data->blobs);
	data->blobs = BlobsInit(data->nbBlob);
}

void BlobLess()
{
	Data *data = DataPointer();
    	data->nbBlob /= 2;
   	if (data->nbBlob < BLOB_MIN)
       		data->nbBlob = BLOB_MIN;
	if (data->blobs.first != NULL)
		BlobsDel(&data->blobs);
	data->blobs = BlobsInit(data->nbBlob);
}

void BlobsRender(LnList *blobs)
{
	Iter iter = Iterate(blobs);
	Blob *blob = Iter_getElem(Blob, &iter);

	while (blob != NULL) {
		BlobRender(blob);

		Iter_next(&iter);
		blob = Iter_getElem(Blob, &iter);
	}
}

void BlobsDel(LnList *blobs)
{
	LnList_clear(blobs);
}