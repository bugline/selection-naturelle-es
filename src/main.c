#include <stdio.h>

#include "core.h"

void MainInit(App *p_App)
{

}

void MainUpdate(App *p_App, float p_Dt)
{

}

void MainRender(App *p_App)
{

}

void MainRemove(App *p_App)
{

}

int main()
{
	App_param param = App_param_default();

	App *app = App_new(param);

	App_setInit(app, &MainInit);
	App_setUpdate(app, &MainUpdate);
	App_setRender(app, &MainRender);
	App_setRemove(app, &MainRemove);

	App_loop(app);
	App_del(app);
	printf("Hello World!");
	return 0;
}