#include "raylib.h"

#ifndef GM_PRAM_H
#define GM_PRAM_H


// Déclaration des structures
typedef struct App_param_window {
	const char *name;
	const char *iconPath;
	Vector2 dim, minDim;
	float ratio;
} App_param_window;

typedef struct App_param_update {
	float fps;
} App_param_update;

typedef struct App_param_render {
	Color bgColor;
} App_param_render;

typedef struct App_param {
	App_param_window window;
	App_param_update update;
	App_param_render render;
} App_param;


// Formes des fonctions
App_param App_param_default(void);

static App_param_window Param_default_window(void);
static App_param_update Param_default_update(void);
static App_param_render Param_default_render(void);


App_param App_param_default(void)
{
	App_param param = { 0 };

	param.window = Param_default_window();
	param.update = Param_default_update();
	param.render = Param_default_render();

	return param;
}

static App_param_window Param_default_window(void)
{
	App_param_window window = { 0 };

	window.name = "Séléction Naturelle ES";
	window.iconPath = "res/icon.png";
	
	window.dim = (Vector2) { 640.f, 360.f };
	window.minDim = (Vector2) { 320.f, 180.f };

	float ratioDim = (float) window.dim.x / (float) window.dim.y;
	float ratioMinDim = (float) window.minDim.x / (float) window.minDim.y;
	if (ratioDim == ratioMinDim) {
		window.ratio = ratioDim;
	} else {
		ERR("Ratio different de dim et de min dim");
	}
	return window;
}

static App_param_update Param_default_update(void)
{
	App_param_update update = { 0 };

	update.fps = 60;

	return update;
}

static App_param_render Param_default_render(void)
{
	App_param_render render = { 0 };

	render.bgColor = (Color) { 0, 0, 0, 255};

	return render;
}

#endif