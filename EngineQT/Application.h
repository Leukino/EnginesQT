#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModulePlayer.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui.h"

#pragma comment (lib, "glew/lib/release/Win32/glew32.lib")
#pragma comment( lib, "glew/lib/release/Win32/glew32s.lib")

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModulePhysics3D* physics;
	ModulePlayer* player;

private:

	Timer	ms_timer;
	float	dt;
	std::list<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};