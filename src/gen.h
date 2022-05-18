#ifndef GEN
#define GEN

#include "gamemaker/core.h"
#include "data.h"


void ProduceNextGen(Data *pData);

void GraphsInit(Data *pData);
void ReducePopGraphPts(UiGraphLine *popGraph, int maxPtsAmout);
void GraphsUpdate(Data *pData);


// GEN
#endif