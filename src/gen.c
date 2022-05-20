#include "gen.h"
#include "data.h"


void ProduceNextGen()
{
	Data *pData = DataPointer();

	int newPopSize = 0;

	Iter iter = Iterate(&pData->blobs);
	Blob *blob = Iter_getElem(Blob, &iter);

	while (blob != NULL) {
		if (blob->score > 1) {
			newPopSize += 2;
		} else if (blob->score > 0) {
			newPopSize++;
		}

		if (blob->score > 0) {
			blob->pos = GetRandBlobPos();
			blob->energy = BLOB_ENERGY;

			if (blob->score > 1) {
				Blob newBlob = BlobMutate(*blob);
				newBlob.pos = GetRandBlobPos();
				newBlob.energy = BLOB_ENERGY;
				newBlob.score = 0;
				LnList_pushFront(Blob, &pData->blobs, &newBlob);
			}

			blob->score = 0;
		} else {
			blob->score = -1;
		}

		Iter_next(&iter);
		blob = Iter_getElem(Blob, &iter);
	}
	
	// Supprime les blobs qui son nuls
	iter = Iterate(&pData->blobs);
	blob = Iter_getElem(Blob, &iter);

	while (blob != NULL) {
		Blob *prevBlob = blob;
		Iter_next(&iter);

		if (blob->score == -1) {
			LnList_rem(&pData->blobs, prevBlob);
		}

		blob = Iter_getElem(Blob, &iter);
	}

	pData->nbBlob = newPopSize;
}

void GraphsInit()
{
	Data *pData = DataPointer();
	// SPEED GRAPHIC
	pData->speedGraph = UiGraphBar_default(pData->nbBlob);

	pData->speedGraph.anch = ANCHOR_NE;
	pData->speedGraph.pos = (Vector2) { -5.f, 5.f };

	pData->speedGraph.colBar = (Color) { 100, 50, 200, 200 };
	pData->speedGraph.colBg = (Color) { 50, 50, 50, 200 };

	pData->speedGraph.xAxis.valRng = (Vector2) { BLOB_MIN_SPEED,
		BLOB_MAX_SPEED };
	pData->speedGraph.xAxis.markStep = 0.5f;


	// Set speed values for the graph
	Iter iter = Iterate(&pData->blobs);
	Blob *blob = Iter_getElem(Blob, &iter);

	while (blob != NULL) {
		UiGraphBar_setVal(&pData->speedGraph, iter.index, blob->speed);
		Iter_next(&iter);
		blob = Iter_getElem(Blob, &iter);
	}
		

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

void ReducePopGraphPts(UiGraphLine *popGraph, int maxPtsAmout)
{
	if (!(popGraph->ptsLen > maxPtsAmout))
		return;

	Vector2 *temp = NEW_ARR(Vector2, maxPtsAmout);

#ifndef RELEASE
	if (!temp) {
		printf("malloc chose to not work in ReducePopGraphPts\n");
		exit(-1);
	}
	if (!popGraph->pts) {
		printf("the points are NULL\n");
		exit(-1);
	}
#endif

	for (int i = 0; i < maxPtsAmout; i++) {
		temp[i] = popGraph->pts[popGraph->ptsLen - maxPtsAmout + i];
	}

	free(popGraph->pts);
	popGraph->pts = temp;

	popGraph->ptsLen = maxPtsAmout;

	popGraph->xAxis.valRng.x = popGraph->pts[0].x;
}

void GraphsUpdate()
{
	Data *pData = DataPointer();
	// Update graph
	UiGraphBar_newValAmnt(&pData->speedGraph, pData->nbBlob);

	// Set speed values for the graph
	Iter iter = Iterate(&pData->blobs);
	Blob *blob = Iter_getElem(Blob, &iter);

	while (blob != NULL) {
		UiGraphBar_setVal(&pData->speedGraph, iter.index, blob->speed);
		Iter_next(&iter);
		blob = Iter_getElem(Blob, &iter);
	}

	pData->genCount++;
	UiGraphLine_addPoint(&pData->popGraph, (Vector2) { pData->genCount,
		pData->nbBlob });
	pData->popGraph.xAxis.valRng.y = pData->genCount;

	ReducePopGraphPts(&pData->popGraph, 60);
}