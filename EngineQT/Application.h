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
#include "ModuleUI.h"
#include "ModuleSimp.h"

//#include "glew/include/GL/glew.h"
#include <gl/glew.h>
#include "SDL/include/SDL_opengl.h"

#include <gl/GL.h>
#include <gl/GLU.h>

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
	ModuleUI* ui;
	ModuleSimp* assimp;

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

	char* vendorChar = "ind";
	char* rendererChar = "ind";

	int cpuCores = -1;
	int systemRAM = -1;
	bool RDTSC, MMX, SSE, SSE2, SSE3, SSE41, SSE42, AVX = false;
	int gpuTotalVram = -1;
	int gpuAvailVram = -1;
	int gpuUsedVram = -1;
private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};