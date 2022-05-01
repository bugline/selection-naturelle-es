#include <math.h>

#include "raylib.h"

float carre(float a)  // Sérieusement ?
{
	return a * a;
}

int CollisionCircle(Vector2 pos1, float radius1, Vector2 pos2, float radius2)
{
	// Fonction non testé
	int collision = 0;

	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;

	float distanceCarre = (carre(dx) + carre(dy));

	if (distanceCarre <= carre(radius1 + radius2))
		collision = 1;

	return collision;
}

int CollisionCircleRec(Vector2 center, float radius, Rectangle rec)
{
	// Fonction non finit
	int collision = 0;

	float dx = fabsf(center.x - rec.x);
	float dy = fabsf(center.y - rec.y);

	if ((carre(dx - rec.width / 2.0f) + carre(dy - rec.width / 2.0f)))
		collision = 1;

	return collision;
}