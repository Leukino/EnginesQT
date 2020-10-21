#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"

//#include "imgui/imgui_impl_opengl2.h"


//#include "imgui/imgui.h"

//#include "imgui/examples/imgui_impl_sdl.h"
//#include "imgui/examples/imgui_impl_win32.h"
//#include "imgui/examples/imgui_impl_opengl3.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glew/lib/release/Win32/glew32.lib")
#pragma comment( lib, "glew/lib/release/Win32/glew32s.lib")

#include "imgui/imgui.h"


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

	//ImGui::Text("char");

	if (GLEW_OK != glewInit())
	{
		LOG("GLEW WENT BRRR");
	}
	else
		LOG("KEKW");
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



