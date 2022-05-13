#ifndef DATA
#define DATA

#include "raylib.h"
#include "gamemaker/core.h"
#include "food.h"
#include "timeSpeed.h"
#include "blob.h"
#include "gen.h"
#include "linked_list.h"
#include "startParam.h"


struct FixUpdtData {
	float incrmnt;
	float fixDt;
	float limExec;
};

typedef struct Data {
	Cam cam;

	StartParam startParam;

	LnList blobs;
	int nbBlob;

	Texture2D foodTex;
	Food *food;
	int nbFood;
	
	TimeSpeed timeSpeed;

	// Movements avec la souris
	Vector2 beforeMouseMove;
	Vector2 mpInitial;

	struct FixUpdtData fixUdpt;

	// Statistics
	UiGraphBar speedGraph;
	UiGraphLine popGraph;

	int genCount;
} Data;

// DATA
#endif