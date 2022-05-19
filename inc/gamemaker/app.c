#include "app.h"
#include "macros.h"
#include "window.h"
#include "draw.h"


// Definition des fonctions
App *App_new(App_param p_Param)
{
	App *newApp = NEW(App);

	newApp->param = p_Param;

	newApp->m_RndIncrmt = 0.0f;

	newApp->Init = NULL;
	newApp->Update = NULL;
	newApp->Render = NULL;
	newApp->Remove = NULL;

	return newApp;
}

void App_del(App *p_App)
{
	free(p_App);
}


// Fonctions pour attribuer les fonctions à appeler
void App_setInit(App *p_App, void (*p_Init) (App *p_App))
{
	p_App->Init = (void (*) (void)) p_Init;
}

void App_setUpdate(App *p_App, void (*p_Update) (App *p_App, float p_Dt))
{
	p_App->Update = (void (*) (void)) p_Update;
}

void App_setRender(App *p_App, void (*p_Render) (App *p_App))
{
	p_App->Render = (void (*) (void)) p_Render;
}

void App_setRemove(App *p_App, void (*p_Remove) (App *p_App))
{
	p_App->Remove = (void (*) (void)) p_Remove;
}


// Fonctions pour appeler les fonctions correspondantes
static void App_callInit(App *p_App)
{
	void (*initFunc) (App *) = (void (*) (App *)) p_App->Init;
	(*initFunc)(p_App);
}

static void App_callUpdate(App *p_App, float p_Dt)
{
	void (*updateFunc) (App *, float) = (void (*) (App *, float)) p_App->Update;
	(*updateFunc)(p_App, p_Dt);
}

static void App_callRender(App *p_App)
{
	void (*renderFunc) (App *) = (void (*) (App *)) p_App->Render;
	(*renderFunc)(p_App);
}

static void App_callRemove(App *p_App)
{
	void (*removeFunc) (App *) = (void (*) (App *)) p_App->Remove;
	(*removeFunc)(p_App);
}


void App_loop(App *p_App)
{
	if (!p_App->Update) {
		ERR("The update function is not set. Set it with:\nApp_setUpdate(app, &updateFunction);");
	}
	if (!p_App->Render) {
		ERR("The render function is not set. Set it with:\nApp_setRender(app, &renderFunction);");
	}

	InitWindow(p_App->param.window.dim.x, p_App->param.window.dim.y,
		p_App->param.window.name);

	if (p_App->Init)
		App_callInit(p_App);

	Image icon = LoadImage(p_App->param.window.iconPath);
	SetWindowIcon(icon);
	
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(p_App->param.window.minDim.x, p_App->param.window.minDim.y);

	if (p_App->param.update.fps > 0.f)
		SetTargetFPS(p_App->param.update.fps);

	double newTime = GetTime();
	p_App->dt = 0.f;
	double lastTime = newTime;

	while (!WindowShouldClose()) {
		App_callUpdate(p_App, p_App->dt);

		p_App->m_RndIncrmt += p_App->dt;
		if (p_App->m_RndIncrmt > p_App->param.render.limitFPS) {
			if (p_App->param.window.autoResize)
				CorrectWin(p_App->param.window.ratio);

			BeginDrawing();
				ClearBackground(p_App->param.render.bgColor);
				App_callRender(p_App);

			p_App->m_RndIncrmt = 0.f;
		}
		EndDrawing();

		newTime = GetTime();	
		p_App->dt = newTime - lastTime;
		lastTime = newTime;
	}

	if (p_App->Remove)
		App_callRemove(p_App);

	CloseWindow();
}