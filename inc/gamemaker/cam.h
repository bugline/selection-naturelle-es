#ifndef GM_CAM_H
#define GM_CAM_H

#include "raylib.h"
#include "app.h"


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


#endif  // GM_CAM_H