#include "mouse.h"


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

	// Ajouter une nouvelle carrote la où est la sourie si click droit
	if (IsMouseButtonPressed(1)) {
		Food newFood;

		newFood.pos = GetScreenToWorld2D(GetMousePosition(),
			pData->cam.camera);
		newFood.size = FOOD_DEF_SIZE;
		newFood.tex = &pData->foodTex;

		LnList_pushBack(Food, &pData->foods, &newFood);
	}
}