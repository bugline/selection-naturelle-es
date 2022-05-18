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


// IMPLEMENTATION

void UiGraphAxis_setLabel(UiGraphAxis *axisPtr, const char *newLabel);


// IMPLEMENTATION

void UiGraphAxis_setLabel(UiGraphAxis *axis, const char *label)
{
	size_t len = strlen(label);
	char *tmp = NEW_ARR(char, len);

	if (tmp == NULL)
		return;
	
	if (axis->m_Label != NULL)
		free(axis->m_Label);

	strcpy(tmp, label);
	axis->m_Label = tmp;
}

#endif  // UI_GRAPH_GRAPH