#include <stdio.h>
#include <string.h>
#include "raylib.h"

typedef struct TimeSpeed {
    float value;
    Font font;
    int change;
    float timeAnim;
    float currTimeAnim;
} TimeSpeed;

void TimeSpeedInit(TimeSpeed *speed)
{
    speed->value = 1.0f;
    speed->font = LoadFont("res/Panipuri.ttf");
    speed->change = 0;
    speed->timeAnim = 0.5;
    speed->currTimeAnim = 0;
}

void TimeSpeedUpdate(TimeSpeed *speed, float *dt)
{
    if (IsKeyPressed(KEY_SPACE)) {
        speed->value = (speed->value == 0) ? 1 : 0;
        speed->change = 1;
    }
    else if (IsKeyPressed(KEY_LEFT)) {
        if (speed->value >= 0.5)
            speed->value /= 2.0f;
        else
            speed->value = 0;
        speed->change = 1;
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        if (speed->value >= 0.5)
            speed->value *= 2.0f;
        else
            speed->value = 0.5;
        speed->change = 1;
    }
}

void TimeSpeedRender(TimeSpeed *speed)
{
    if (speed->change) {
        speed->currTimeAnim = GetTime();
        speed->change = 0;
    }
    if (GetTime()  < speed->currTimeAnim + speed->timeAnim) {
        char num[8];
        gcvt(speed->value, 8, num);
        char text[9] = "x";
        strcat(text, num);
        DrawTextEx(speed->font, text, (Vector2) { 200, 200 }, 50, 10, (Color) { 255, 255, 255, 255 });
    }
    else {
        speed->currTimeAnim = 0;
        speed->change = 0;
    }
    
}