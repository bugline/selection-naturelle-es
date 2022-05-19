#ifndef GM_PRAM_H
#define GM_PRAM_H

#include "raylib.h"
#include <stdbool.h>


// Déclaration des structures
typedef struct App_param_window {
	const char *name;
	const char *iconPath;
	Vector2 dim, minDim;
	float ratio;
	bool autoResize;
} App_param_window;

typedef struct App_param_update {
	float fps;
} App_param_update;

typedef struct App_param_render {
	Color bgColor;
	float limitFPS;
} App_param_render;

typedef struct App_param {
	App_param_window window;
	App_param_update update;
	App_param_render render;
} App_param;


// Formes des fonctions
App_param App_param_default(void);

App_param_window Param_default_window(void);
App_param_update Param_default_update(void);
App_param_render Param_default_render(void);


#endif