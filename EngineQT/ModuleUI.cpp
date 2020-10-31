#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

#pragma comment (lib, "glew/lib/release/Win32/glew32.lib")
#pragma comment( lib, "glew/lib/release/Win32/glew32s.lib")

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleUI::~ModuleUI()
{
}

// Render not available yet----------------------------------
bool ModuleUI::Init()
{
	bool ret = true;
	return ret;
}

// ---------------------------------------------------------
bool ModuleUI::Start()
{
	return true;
}

// ---------------------------------------------------------
update_status ModuleUI::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModuleUI::Update(float dt)
{
    
	

   // SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModuleUI::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleUI::CleanUp()
{

	return true;
}

