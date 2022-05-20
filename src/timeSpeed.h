#ifndef TIMESPEED
#define TIMESPEED

#include <string.h>
#include "raylib.h"
#include "gamemaker/core.h"

#define MIN_TIME_SPEED 0.25
#define MAX_TIME_SPEED 1e5


typedef struct TimeSpeed {
    float value;
    int change;
    float timeAnim;
    float currTimeAnim;
    UiText uiText;
} TimeSpeed;


void TimeSpeedInit(TimeSpeed *tSpeed);
void TimeSpeedLess();
void TimeSpeedMore();
void TimeSpeedUpdate(TimeSpeed *tSpeed, float *dt);
void TimeSpeedRender(TimeSpeed *tSpeed);
void TimeSpeedDel(TimeSpeed *tSpeed);


// TIMESPEED
#endif