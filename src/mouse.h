#ifndef MOUSE
#define MOUSE

#include "data.h"

#define CAM_MIN_ZOOM      20
#define CAM_MAX_ZOOM     400
#define CAM_SCROLL_SPEED   0.2f
#define CAM_MOUSE_SPEED    0.002f
#define CAM_KEY_SPEED     60


void MouseUpdate(Data *pData);


#endif  // MOUSE