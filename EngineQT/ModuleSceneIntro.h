#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();


	//void MainMenuBar();

	//void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

};
