#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"

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

	ImGui::Text("char");


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	char title[80];
	sprintf_s(title, "Game engine");
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



