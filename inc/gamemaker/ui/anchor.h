#ifndef GM_UI_ANCHOR
#define GM_UI_ANCHOR

#include "raylib.h"


typedef char Anchor;


// All anchors
#define ANCHOR_NW  0
#define ANCHOR_NE  1
#define ANCHOR_SW  2
#define ANCHOR_SE  3
#define ANCHOR_C   4
#define ANCHOR_W   5
#define ANCHOR_N   6
#define ANCHOR_E   7
#define ANCHOR_S   8


Vector2 AnchGetOrig(char anchor);
Vector2 AnchGetRecC(Vector2 pos, Vector2 size, char anchor);   // Center
Vector2 AnchGetRecTL(Vector2 pos, Vector2 size, char anchor);  // Top left
Vector2 AnchGetRecTR(Vector2 pos, Vector2 size, char anchor);  // Top right
Vector2 AnchGetRecBL(Vector2 pos, Vector2 size, char anchor);  // Bottom left
Vector2 AnchGetRecBR(Vector2 pos, Vector2 size, char anchor);  // Bottom right


#endif  // GM_UI_ANCHOR