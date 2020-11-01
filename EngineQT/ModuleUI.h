#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleUI : public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void MainMenuBar();

private:

	int fps = 60;
	bool vsync = false;
	


	bool specMenu = false;
	bool fullscreen = false;
	bool debug;
};