#include "graph.h"


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