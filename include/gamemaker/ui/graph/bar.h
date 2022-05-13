#ifndef UI_GRAPH_BAR
#define UI_GRAPH_BAR

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "../../macros.h"
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


// IMPLEMENTATION

UiGraphBar UiGraphBar_default(int valLen)
{
	UiGraphBar graph;

	graph.pos = (Vector2) { 0.f, 0.f };
	graph.size = (Vector2) { 400.f, 300.f };
	graph.anch = ANCHOR_C;

	graph.values = NEW_ARR(float, valLen);
	memset(graph.values, 0, sizeof(float) * valLen);
	graph.valLen = valLen;

	graph.xAxis.m_Label = NULL;
	UiGraphAxis_setLabel(&graph.xAxis, "x axis");
	graph.xAxis.valRng = (Vector2) { 0.f, 100.f };
	graph.xAxis.markStep = 10.f;

	graph.yAxis.m_Label = NULL;
	UiGraphAxis_setLabel(&graph.yAxis, "y axis");
	graph.yAxis.valRng = (Vector2) { 0.f, 20.f };
	graph.yAxis.markStep = 2.f;

	graph.margin = 5.f;

	graph.font = GetFontDefault();
	graph.fontSize = 14.f;

	graph.colFg = RAYWHITE;
	graph.colBg = (Color) { 50, 50, 50, 255 };
	graph.colBar = MAGENTA;

	return graph;
}


void UiGraphBar_setVal(UiGraphBar *graph, int index, float value)
{
	if (graph->values != NULL && index < graph->valLen)
		graph->values[index] = value;
}


void UiGraphBar_newValAmnt(UiGraphBar *graph, int amount)
{
	if (graph->values)
		free(graph->values);

	if (amount > 0)
		graph->values = NEW_ARR(float, amount);
	else
		graph->values = NULL;
	
	graph->valLen = amount;
}


float *_GetFrequ(float *values, int valLen, Vector2 range, float step)
{
	int frequLen = floorf((range.y - range.x) / step);

	float *frequ = NEW_ARR(float, frequLen);
	if (frequ == NULL)
		return NULL;

	memset(frequ, 0, sizeof(float) * frequLen);
	float probability = 1.f / valLen;

	for (int i = 0; i < valLen; i++) {
		int category = floorf((values[i] - range.x) / step);
		
		if (category < 0)
			frequ[0] += probability;
		else if (category < frequLen)
			frequ[category] += probability;
		else
			frequ[frequLen - 1] += probability;
	}
	return frequ;
}


void _DrawBars(const UiGraphBar *graph)
{
	if (graph->values == NULL) {
		return;
	}

	Vector2 tl = AnchGetRecTL(graph->pos, graph->size, graph->anch);
	Vector2 br = AnchGetRecBR(graph->pos, graph->size, graph->anch);

	float rng = graph->xAxis.valRng.y - graph->xAxis.valRng.x;

#ifndef RELEASE
	if (rng < graph->xAxis.markStep) {
		printf("A step of %f can't cut a range of %f\n",
			graph->xAxis.markStep, rng);
		exit(-1);
	}
#endif

	int frequLen = (int) ceilf(rng / graph->xAxis.markStep);
	float *frequences = _GetFrequ(graph->values, graph->valLen,
		graph->xAxis.valRng, graph->xAxis.markStep);

	float graphStep = (graph->xAxis.markStep / rng) * (br.x - tl.x);
	
	for (int i = 0; i < frequLen; i++) {
		float barH = frequences[i] * (br.y - tl.y);
		
		DrawRectangle(tl.x + graphStep * i + 1, br.y - barH,
			graphStep - 2, barH, graph->colBar);
	}
}


void _DrawText(const UiGraphBar *graph)
{
#ifndef RELEASE
	if (!graph->xAxis.m_Label) {
		printf("No label is set for the x Axis\n");
		exit(-1);
	}
	if (!graph->yAxis.m_Label) {
		printf("No label is set for the y Axis\n");
		exit(-1);
	}
#endif

	Vector2 tl = AnchGetRecTL(graph->pos, graph->size, graph->anch);
	Vector2 br = AnchGetRecBR(graph->pos, graph->size, graph->anch);

	Vector2 margins = (Vector2) { graph->margin, graph->margin };
	DrawTextEx(graph->font, graph->yAxis.m_Label, Vector2Add(tl, margins),
		graph->fontSize, graph->fontSize / 10.f, graph->colFg);
	
	Vector2 textSize = MeasureTextEx(graph->font, graph->xAxis.m_Label,
		graph->fontSize, graph->fontSize / 10.f);

	DrawTextEx(graph->font, graph->xAxis.m_Label,
		Vector2Subtract(br, Vector2Add(margins, textSize)),
		graph->fontSize, graph->fontSize / 10.f, graph->colFg);

	DrawTextEx(graph->font, "50%",
		(Vector2) { tl.x + graph->margin, (br.y + tl.y - textSize.y) / 2.f },
		graph->fontSize, graph->fontSize / 10.f, graph->colFg);
}


void UiGraphBar_render(const UiGraphBar *graph)
{
	BeginBlendMode(BLEND_ALPHA);

	// Bg
	Vector2 pos = AnchGetRecTL(graph->pos, graph->size, graph->anch); 
	DrawRectangleV(pos, graph->size, graph->colBg);

	_DrawBars(graph);
	_DrawText(graph);

	EndBlendMode();
}


void UiGraphBar_del(UiGraphBar *graph)
{
	if (graph->xAxis.m_Label)
		free(graph->xAxis.m_Label);
	if (graph->yAxis.m_Label)
		free(graph->yAxis.m_Label);
	if (graph->values)
		free(graph->values);
}


#endif  // UI_GRAPH_BAR