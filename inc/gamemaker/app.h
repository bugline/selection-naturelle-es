#ifndef GM_APP_H
#define GM_APP_H

#include "raylib.h"
#include "param.h"


typedef struct App {
	App_param param;

	float dt;  // delta temps

	float m_RndIncrmt;

	void (*Init) (void);
	void (*Update) (void);
	void (*Render) (void);
	void (*Remove) (void);	
} App;


// Forme des fonctions
App *App_new();
void App_del(App *app);

void App_setInit(App *app, void (*init) (App *app));
void App_setUpdate(App *app, void (*update) (App *app, float deltaTime));
void App_setRender(App *app, void (*render) (App *app));
void App_setRemove(App *app, void (*remove) (App *app));

void App_loop(App *app);


#endif  // GM_APP_H