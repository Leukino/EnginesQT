#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/Importer.hpp"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include <iostream>

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
	aiLogStream();
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	aiDetachAllLogStreams();
	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	//ImGui::NewFrame();
	char title[80];
	sprintf_s(title, "Game engine");
	App->window->SetTitle(title);

	

	return UPDATE_CONTINUE;
}



