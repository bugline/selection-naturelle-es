#include <stdio.h>
#include <string.h>
#include "raylib.h"

typedef struct Speed {
    float value;
    Font font;
    int change;
    float timeAnim;
    float currTimeAnim;
} Speed;

void SpeedInit(Speed *speed)
{
    speed->value = 1.0f;
    speed->font = LoadFont("res/Panipuri.ttf");
    speed->change = 0;
    speed->timeAnim = 0.5;
    speed->currTimeAnim = 0;
}

void SpeedUpdate(Speed *speed, float *dt)
{
    if (IsKeyPressed(KEY_Q)) {
        printf("bonjour");
        if (speed->value >= 0.5)
            speed->value /= 2.0f;
        else
            speed->value = 0;
        speed->change = 1;
    }
    else if (IsKeyPressed(KEY_S)) {
        if (speed->value >= 0.5)
            speed->value *= 2.0f;
        else
            speed->value = 0.5;
        speed->change = 1;
    }
}

void SpeedRender(Speed *speed)
{
    if (speed->change) {
        if (!speed->currTimeAnim)
            speed->currTimeAnim = GetTime();
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
}