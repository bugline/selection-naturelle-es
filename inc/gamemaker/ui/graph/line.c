#include "line.h"
#include "raymath.h"


UiGraphLine UiGraphLine_default()
{
	UiGraphLine graph;

	graph.pos = (Vector2) { 0.f, 0.f };
	graph.size = (Vector2) { 400.f, 300.f };
	graph.anch = ANCHOR_C;

	graph.pts = NULL;
	graph.ptsLen = 0;

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
	graph.colLine = MAGENTA;

	return graph;
}


void UiGraphLine_setPoint(UiGraphLine *graph, int index, Vector2 pt)
{
#ifndef RELEASE
	if (graph->pts == NULL) {
		printf("there isn't even a point in the list, so the point %d doesn't exist\n",
			index);
		exit(-1);
	}
	
	if (graph->ptsLen <= index) {
		printf("no point number %d, the list is %d long\n", index,
			graph->ptsLen);
		exit(-1);
	}
#endif
		graph->pts[index] = pt;
}


void UiGraphLine_addPoint(UiGraphLine *graph, Vector2 pt)
{
	Vector2 *tmp = NEW_ARR(Vector2, graph->ptsLen + 1);

	if (tmp == NULL) {
#ifndef RELEASE
		printf("malloc failed in UiGraphLine_addPoint\n");
#endif
		return;
	}

	int i = 0;
	bool isAdded = false;
	while (i < graph->ptsLen + 1) {
		if (!isAdded) {
			if (i == graph->ptsLen) {
				tmp[i] = pt;
				isAdded = true;
			} else if (pt.x < graph->pts[i].x) {
				tmp[i] = pt;
				isAdded = true;
			} else {
				tmp[i] = graph->pts[i];
			}
		} else {
			tmp[i] = graph->pts[i + 1];
		}

		i++;
	}

	if (graph->pts)
		free(graph->pts);

	graph->pts = tmp;
	graph->ptsLen++;
}


Vector2 _PutVecInRng(Vector2 vec, Vector2 rngX, Vector2 rngY, Vector2 graphLen)
{
	return (Vector2) {
		(vec.x - rngX.x) / (rngX.y - rngX.x) * graphLen.x,
		(1 - (vec.y - rngY.x) / (rngY.y - rngY.x)) * graphLen.y,
	};
}


void _DrawLines(const UiGraphLine *graph)
{
	if (graph->pts == NULL) {
		return;
	}

	Vector2 tl = AnchGetRecTL(graph->pos, graph->size, graph->anch);

	float rngX = graph->xAxis.valRng.y - graph->xAxis.valRng.x;
	float rngY = graph->xAxis.valRng.y - graph->xAxis.valRng.x;

#ifndef RELEASE
	if (rngX < graph->xAxis.markStep) {
		printf("A step for the x axis of %f can't cut a range of %f\n",
			graph->xAxis.markStep, rngX);
		exit(-1);
	}
	if (rngY < graph->yAxis.markStep) {
		printf("A step for the y axis of %f can't cut a range of %f\n",
			graph->yAxis.markStep, rngY);
		exit(-1);
	}
#endif

	Vector2 prevPt = Vector2Add(tl, _PutVecInRng(graph->pts[0],
		graph->xAxis.valRng, graph->yAxis.valRng, graph->size));
	DrawCircleV(prevPt, 2, graph->colLine);

	for (int i = 1; i < graph->ptsLen; i++) {
		Vector2 graphPos = Vector2Add(tl, _PutVecInRng(graph->pts[i],
			graph->xAxis.valRng, graph->yAxis.valRng, graph->size));
		DrawLineV(prevPt, graphPos, graph->colLine);
		DrawCircleV(graphPos, 2, graph->colLine);

		prevPt = graphPos;
	}
}


void _DrawTextLine(const UiGraphLine *graph)
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

	// DrawTextEx(graph->font, "50%",
	// 	(Vector2) { tl.x + graph->margin, (br.y + tl.y - textSize.y) / 2.f },
	// 	graph->fontSize, graph->fontSize / 10.f, graph->colFg);
}


void UiGraphLine_render(const UiGraphLine *graph)
{
	BeginBlendMode(BLEND_ALPHA);

	// Bg
	Vector2 pos = AnchGetRecTL(graph->pos, graph->size, graph->anch); 
	DrawRectangleV(pos, graph->size, graph->colBg);

	_DrawLines(graph);
	_DrawTextLine(graph);

	EndBlendMode();
}


void UiGraphLine_del(UiGraphLine *graph)
{
	if (graph->xAxis.m_Label)
		free(graph->xAxis.m_Label);
	if (graph->yAxis.m_Label)
		free(graph->yAxis.m_Label);
	if (graph->pts)
		free(graph->pts);
}