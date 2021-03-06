#include "param.h"

#include "macros.h"


App_param App_param_default(void)
{
	App_param param = { 0 };

	param.window = Param_default_window();
	param.update = Param_default_update();
	param.render = Param_default_render();

	return param;
}

/*------------------------------------------------------------------*/

App_param_window Param_default_window(void)
{
	App_param_window window = { 0 };

	window.name = "Game";
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

	window.autoResize = true;

	return window;
}

/*------------------------------------------------------------------*/

App_param_update Param_default_update(void)
{
	App_param_update update = { 0 };

	update.fps = 60;

	return update;
}

/*------------------------------------------------------------------*/

App_param_render Param_default_render(void)
{
	App_param_render render = { 0 };

	render.bgColor = (Color) { 0, 0, 0, 255};
	render.limitFPS = 0;

	return render;
}