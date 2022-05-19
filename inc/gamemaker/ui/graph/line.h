#ifndef UI_GRAPH_LINE
#define UI_GRAPH_LINE

#include "graph.h"
#include "../anchor.h"


typedef struct UiGraphLine {
	Vector2 pos;
	Vector2 size;
	Anchor anch;

	Vector2 *pts;
	int ptsLen;

	UiGraphAxis xAxis;
	UiGraphAxis yAxis;

	float margin;

	Font font;
	float fontSize;

	Color colFg;
	Color colBg;
	Color colLine;
} UiGraphLine;


// DEFINES

UiGraphLine UiGraphLine_default();
void UiGraphLine_setPoint(UiGraphLine *graph, int index, Vector2 point);
// void UiGraphLine_newValAmnt(UiGraphLine *graph, int amount);
void UiGraphLine_addPoint(UiGraphLine *graph, Vector2 point);
void UiGraphLine_render(const UiGraphLine *graph);
void UiGraphLine_del(UiGraphLine *graph);


#endif  // UI_GRAPH_LINE