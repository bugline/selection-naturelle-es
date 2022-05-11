#ifndef GEN
#define GEN

#include "gamemaker/core.h"
#include "data.h"



void ProduceNextGen(Data *pData)
{
	int newPopSize = 0;
	for (int i = 0; i < pData->nbBlob; i++) {
		newPopSize += pData->blob[i].score;
	}

	Blob *tmp = NEW_ARR(Blob, newPopSize);
	int tmpLen = 0;

	for (int i = 0; i < pData->nbBlob; i++) {
		if (pData->blob[i].score > 0) {
			tmp[tmpLen] = pData->blob[i];
			tmp[tmpLen].pos = GetRandBlobPos();
			tmp[tmpLen].score = 0;
			tmpLen++;

			// Enfants
			if (pData->blob[i].score > 1) {
				tmp[tmpLen] = BlobMutate(pData->blob[i]);
				tmp[tmpLen].pos = GetRandBlobPos();
				tmp[tmpLen].score = 0;
				tmpLen++;
			}
		}
	}

	free(pData->blob);
	pData->blob = tmp;
	pData->nbBlob = tmpLen;
}

void GraphsInit(Data *pData)
{
	// SPEED GRAPHIC
	pData->speedGraph = UiGraphBar_default(pData->nbBlob);

	pData->speedGraph.anch = ANCHOR_NE;
	pData->speedGraph.pos = (Vector2) { -5.f, 5.f };

	pData->speedGraph.colBar = (Color) { 100, 50, 200, 200 };
	pData->speedGraph.colBg = (Color) { 50, 50, 50, 200 };

	pData->speedGraph.xAxis.valRng = (Vector2) { BLOB_MIN_SPEED,
		BLOB_MAX_SPEED };
	pData->speedGraph.xAxis.markStep = 0.5f;

	for (int i = 0; i < pData->nbBlob; i++)
		UiGraphBar_setVal(&pData->speedGraph, i, pData->blob[i].speed);

	UiGraphAxis_setLabel(&pData->speedGraph.xAxis, "speed");
	UiGraphAxis_setLabel(&pData->speedGraph.yAxis, "blob amount");

	// POPULATION GRAPHIC
	UiGraphLine g = UiGraphLine_default();

	g.anch = ANCHOR_SE;
	g.pos = (Vector2) { -5.f, -5.f };

	g.colLine = (Color) { 250, 150, 75, 200 };
	g.colBg = (Color) { 50, 50, 50, 200 };

	UiGraphAxis_setLabel(&g.xAxis, "time");
	UiGraphAxis_setLabel(&g.yAxis, "population amount");

	g.xAxis.valRng = (Vector2) { 0.f, 1.f };
	g.yAxis.valRng = (Vector2) { 0.f, 105.f };

	g.xAxis.markStep = 1.f;
	g.yAxis.markStep = 1.f;
	
	pData->genCount = 0;
	UiGraphLine_addPoint(&g, (Vector2) { 0, pData->nbBlob });

	pData->popGraph = g;
}

void GraphsUpdate(Data *pData)
{
	// Update graph
	UiGraphBar_newValAmnt(&pData->speedGraph, pData->nbBlob);
	for (int i = 0; i < pData->nbBlob; i++)
		UiGraphBar_setVal(&pData->speedGraph, i, pData->blob[i].speed);

	pData->genCount++;
	UiGraphLine_addPoint(&pData->popGraph, (Vector2) { pData->genCount,
		pData->nbBlob });
	pData->popGraph.xAxis.valRng.y = pData->genCount;
}

// GEN
#endif