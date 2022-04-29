#include <stdio.h>

#include "gamemaker/core.h"
#include "blob.h"


typedef struct Data {
	Cam cam;
	Blob *blob;
	int nbBlob;
} Data;

Data data;


void MainInit(App *p_App)
{
	data.cam = Cam_init(100);
	data.nbBlob = 100;
	data.blob = BlobsInit(data.nbBlob);
}

void MainUpdate(App *p_App, float p_Dt)
{
	if (IsKeyDown(KEY_UP))
		data.cam.camera.target.y -= 1;
	else if (IsKeyDown(KEY_DOWN))
		data.cam.camera.target.y += 1;
	else if (IsKeyDown(KEY_LEFT))
		data.cam.camera.target.x -= 1;
	else if (IsKeyDown(KEY_RIGHT))
		data.cam.camera.target.x += 1;
}

void MainRender(App *p_App)
{
	Cam_start(&data.cam, p_App);

	BlobsRender(data.blob, data.nbBlob);
	
	Cam_stop();

	DrawFPS(10, 10);
}

void MainRemove(App *p_App)
{
	if (data.blob)
		free(data.blob);
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
	
	return 0;
}