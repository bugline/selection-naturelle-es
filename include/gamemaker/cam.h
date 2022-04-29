#ifndef GM_CAM_H
#define GM_CAM_H

#include "raylib.h"

#include "app.h"
#include "macros.h"


typedef struct Cam {
	Camera2D camera;
	float fov;  // Le nombre de mètres affichés dans la largeure
} Cam;


Cam Cam_init(float fov);

Cam *Cam_new(float fov);
void Cam_del(Cam *cam);

void Cam_prepRender(Cam *cam, App *app);
void Cam_start(Cam *cam, App *app);
void Cam_stop(void);

Vector2 Cam_getPos(Cam *cam);
void Cam_setPos(Cam *cam, Vector2 newVec);

float Cam_getRot(Cam *cam);
void Cam_setRot(Cam *cam, float newRot);


Cam Cam_init(float p_Fov)
{
	Cam newCam = { 0 };

	Camera2D camera = {
		(Vector2) { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f },
		(Vector2) { 0.f, 0.f },
		0.f,
		GetScreenWidth() / p_Fov
	};
	newCam.camera = camera;
	newCam.fov = p_Fov;

	return newCam;
}

Cam *Cam_new(float p_Fov)
{
	Cam *newCam = NEW(Cam);

	Camera2D camera = {
		(Vector2) { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f },
		(Vector2) { 0.f, 0.f },
		0.f,
		GetScreenWidth() / p_Fov
	};
	newCam->camera = camera;
	newCam->fov = p_Fov;

	return newCam;
}

void Cam_del(Cam *p_Cam)
{
	free(p_Cam);
}

void Cam_prepRender(Cam *p_Cam, App *p_App)
{
	p_Cam->camera.offset = (Vector2) { GetScreenWidth() / 2.f,
		GetScreenHeight() / 2.f };
	p_Cam->camera.zoom = GetScreenWidth() / p_Cam->fov;
}

void Cam_start(Cam *p_Cam, App *p_App)
{
	Cam_prepRender(p_Cam, p_App);
	BeginMode2D(p_Cam->camera);
}

void Cam_stop(void)
{
	EndMode2D();
}

Vector2 Cam_getPos(Cam *p_Cam)
{
	return p_Cam->camera.target;
}

void Cam_setPos(Cam *p_Cam, Vector2 newVec)
{
	p_Cam->camera.target = newVec;
}

float Cam_getRot(Cam *p_Cam)
{
	return p_Cam->camera.rotation;
}

void Cam_setRot(Cam *p_Cam, float newRot)
{
	p_Cam->camera.rotation = newRot;
}


#endif  // GM_CAM_H