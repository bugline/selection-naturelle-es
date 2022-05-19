#include "window.h"


void CorrectWin(float ratio)
{
	static int prevWidth = 0;
	static int prevHeight = 0;

	static int prevResized = 0;

	if (IsWindowResized()) {
		prevResized = 1;
		return;
	}

	int width = GetScreenWidth();
	int height = GetScreenHeight();

	
	if (prevResized) {
		if (width != prevWidth) {
			SetWindowSize(width, width / ratio);
		} else if (height != prevHeight) {
			SetWindowSize(height * ratio, height);
		}
	}
	prevResized = 0;
	prevWidth = GetScreenWidth();
	prevHeight = GetScreenHeight();
}