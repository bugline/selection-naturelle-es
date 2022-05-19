#include "timeSpeed.h"

#include <math.h>


void TimeSpeedInit(TimeSpeed *tSpeed)
{
    tSpeed->value = 1.0f;
    tSpeed->change = 0;
    tSpeed->timeAnim = 0.666;
    tSpeed->currTimeAnim = 0;

    Font font = LoadFont("res/Panipuri.ttf");
    UiText_init(&tSpeed->uiText, "", font, 60, (Vector2) { 0, 0 }, ANCHOR_C, WHITE);
}

void TimeSpeedUpdate(TimeSpeed *tSpeed, float *dt)
{
    if (IsKeyPressed(KEY_SPACE)) {
        tSpeed->value = (tSpeed->value == 0) ? 1 : 0;
        tSpeed->change = 1;
    }
    else if (IsKeyPressed(KEY_LEFT)) {
        if (tSpeed->value >= MIN_TIME_SPEED)
            tSpeed->value /= 2.0f;
        else
            tSpeed->value = 0;
        tSpeed->change = 1;
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        if (tSpeed->value >= MIN_TIME_SPEED) {
            if (tSpeed->value < MAX_TIME_SPEED)
                tSpeed->value *= 2.0f;
        }
        else
            tSpeed->value = MIN_TIME_SPEED;
        tSpeed->change = 1;
    }
}

void TimeSpeedRender(TimeSpeed *tSpeed)
{
    if (tSpeed->change) {
        tSpeed->currTimeAnim = GetTime();
        tSpeed->change = 0;
    }
    if (GetTime()  < tSpeed->currTimeAnim + tSpeed->timeAnim) {
        char *num = NEW_ARR(char, 8);
	memset(num, '\0', 8);
        gcvt(tSpeed->value, 8, num);

        char *text = NEW_ARR(char, 9);
	memset(text, '\0', 9);
	text[0] = 'x';
        strcat(text, num);

	UiText_chngTxt(&tSpeed->uiText, text);

	free(num);
	free(text);

	if (tSpeed->timeAnim != 0.f) {
		float alpha = (GetTime() - tSpeed->currTimeAnim) /
			tSpeed->timeAnim;
		tSpeed->uiText.mCol.a = roundf((1.f - alpha) * 255);
	}

        UiText_render(&tSpeed->uiText);
    }
    else {
        tSpeed->currTimeAnim = 0;
        tSpeed->change = 0;
    }
}

void TimeSpeedDel(TimeSpeed *tSpeed)
{
    UiText_del(&tSpeed->uiText);
}