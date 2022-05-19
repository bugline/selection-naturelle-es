#ifndef UI_GRAPH_BAR
#define UI_GRAPH_BAR

#include "raylib.h"
#include "../anchor.h"
#include "graph.h"


typedef struct UiGraphBar {
	Vector2 pos;
	Vector2 size;
	Anchor anch;

	float *values;
	int valLen;

	UiGraphAxis xAxis;
	UiGraphAxis yAxis;

	float margin;

	Font font;
	float fontSize;

	Color colFg;
	Color colBg;
	Color colBar;
} UiGraphBar;


// IMPLEMENTATION

UiGraphBar UiGraphBar_default(int valuesAmount);
void UiGraphBar_setVal(UiGraphBar *graph, int index, float value);
void UiGraphBar_newValAmnt(UiGraphBar *graph, int amount);
void UiGraphBar_render(const UiGraphBar *graph);
void UiGraphBar_del(UiGraphBar *graph);


#endif  // UI_GRAPH_BAR