#include "Globals.h"
#include "Application.h"
#include "ModuleSimp.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/Importer.hpp"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include <iostream>

ModuleSimp::ModuleSimp(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSimp::~ModuleSimp()
{}

// Load assets
bool ModuleSimp::Start()
{
	//struct aiLogStream stream;
	//stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	//aiAttachLogStream(&stream);
	//aiLogStream();
	return true;
}

// Unload assets
bool ModuleSimp::CleanUp()
{
	//aiDetachAllLogStreams();
	return true;
}

// Update: draw background
update_status ModuleSimp::Update(float dt)
{
	LOG("HELLO I'M MODULE SIMP HAHAXD123");
	return UPDATE_CONTINUE;
}