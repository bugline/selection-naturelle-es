#ifndef DATA
#define DATA

#include "raylib.h"
#include "gamemaker/core.h"
#include "food.h"
#include "timeSpeed.h"
#include "blob.h"
#include "linked_list.h"
#include "ui.h"

#define STATE_MENU 1
#define STATE_RUN 2


struct FixUpdtData {
	float incrmnt;
	float fixDt;
	float limExec;
};

typedef struct Data {
	Cam cam;

	char state;

	Ui ui;

	LnList blobs;
	int nbBlob;

	Texture2D foodTex;
	LnList foods;
	int nbFood;
	int nbFoodFix;
	int foodVariance;
	
	TimeSpeed timeSpeed;

	// Movements avec la souris
	Vector2 beforeMouseMove;
	Vector2 mpInitial;

	struct FixUpdtData fixUdpt;

	// Statistics
	UiGraphBar speedGraph;
	UiGraphLine popGraph;

	int genCount;

	bool simulEnd;
} Data;

Data *DataPointer(void);

#endif  // DATA