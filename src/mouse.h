#ifndef MOUSE
#define MOUSE

#include "data.h"

#define CAM_MIN_ZOOM      20
#define CAM_MAX_ZOOM     400
#define CAM_SCROLL_SPEED   0.2f
#define CAM_MOUSE_SPEED    0.002f
#define CAM_KEY_SPEED     60


void MouseUpdate(Data *pData)
{
    // Mouvements avec la souris
	pData->cam.fov += pData->cam.fov * -CAM_SCROLL_SPEED * GetMouseWheelMove();
	if (pData->cam.fov < CAM_MIN_ZOOM)
		pData->cam.fov = CAM_MIN_ZOOM;
	else if (pData->cam.fov > CAM_MAX_ZOOM)
		pData->cam.fov = CAM_MAX_ZOOM;
	
	if (IsMouseButtonPressed(0)) {
		pData->mpInitial = GetMousePosition();
		pData->beforeMouseMove = Cam_getPos(&pData->cam);
	} else if (IsMouseButtonReleased(0) || IsMouseButtonDown(0)) {
		Vector2 mpDelta = Vector2Subtract(pData->mpInitial,
			GetMousePosition());
		Vector2 newPos = Vector2Add(pData->beforeMouseMove,
			Vector2Scale(mpDelta, 1.f * pData->cam.fov *
				CAM_MOUSE_SPEED));
		Cam_setPos(&pData->cam, newPos);
	}

	if (IsMouseButtonPressed(1)) {
		Food param = *pData->food;
		param.pos = GetScreenToWorld2D(GetMousePosition(), pData->cam.camera);
		param.eaten = false;
		pData->food = NewFood(pData->food, param);
	}
}

// MOUSE
#endif