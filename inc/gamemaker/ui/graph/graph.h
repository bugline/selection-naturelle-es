#ifndef UI_GRAPH_GRAPH
#define UI_GRAPH_GRAPH

#include "raylib.h"
#include <string.h>
#include "../../macros.h"


typedef struct UiGraphAxis {
	char *m_Label;  // use setLabel() to change it
	Vector2 valRng;
	float markStep;
} UiGraphAxis;


void UiGraphAxis_setLabel(UiGraphAxis *axisPtr, const char *newLabel);


#endif  // UI_GRAPH_GRAPH