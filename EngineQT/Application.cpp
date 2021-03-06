#include "Application.h"
#include <string>

using namespace std;
Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	physics = new ModulePhysics3D(this);
	player = new ModulePlayer(this);
	ui = new ModuleUI(this);
	assimp = new ModuleSimp(this);
	

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(assimp);
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(physics);
	
	//AddModule(assimp);

	// Scenes
	AddModule(player);
	AddModule(scene_intro);

	// Renderer last!
	AddModule(ui);
	AddModule(renderer3D);

}

Application::~Application()
{

	std::list<Module*>::reverse_iterator item = list_modules.rbegin();

	while (item != list_modules.rend())
	{
		delete (*item);
		item++;
	}
}

bool Application::Init()
{
	bool ret = true;

	//InitSeed();

	// Call Init() in all modules
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret; ++item)
	{
		ret = (*item)->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret; ++item)
	{
		ret = (*item)->Start();
	}

	cpuCores = SDL_GetCPUCount(); 
	systemRAM = SDL_GetSystemRAM();
	RDTSC = SDL_HasRDTSC();
	MMX = SDL_HasMMX();
	SSE = SDL_HasSSE();
	SSE2 = SDL_HasSSE2();
	SSE3 = SDL_HasSSE3();
	SSE41 = SDL_HasSSE41();
	SSE42 = SDL_HasSSE42();
	AVX = SDL_HasAVX();
	vendorChar = (char*)glGetString(GL_VENDOR);
	rendererChar = (char*)glGetString(GL_RENDERER);
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &(int)gpuTotalVram);
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &(int)gpuAvailVram);
	//glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &(int)gpuUsedVram);
	LOG("CPU CORES: %d, RAM: %f GB", cpuCores, systemRAM* 0.0009765625);
	LOG("Graphics card: %s, Vendor: %s", rendererChar, vendorChar);
	LOG("Total VRAM: %f MB, Available VRAM: %f MB", (float)gpuTotalVram, (float)gpuAvailVram/*, (float)gpuUsedVram*/);

	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_log.push_back(ms_timer.Read());
	fps_log.push_back(1.0f / dt);
	if (ms_log.size() > vector_limit) { // ms and fps fill at the same time, so only need top check one
		ms_log.erase(ms_log.begin());
		fps_log.erase(fps_log.begin());
	}
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();

	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; ++item)
	{
		ret = (*item)->PreUpdate(dt);
	}

	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; ++item)
	{
		ret = (*item)->Update(dt);
	}

	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; ++item)
	{
		ret = (*item)->PostUpdate(dt);
	}


	FinishUpdate();
	if (escape)
		return UPDATE_STOP;
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::list<Module*>::iterator item = list_modules.begin();

	while (*item != NULL && ret == true)
	{
		ret = (*item)->CleanUp();
		item--;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	//list_modules.add(mod);
	list_modules.push_back(mod);
}