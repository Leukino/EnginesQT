#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "imgui/imgui.h"

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
	if (GLEW_OK != glewInit())
	{
		LOG("GLEW WENT BRRR");
	}
	else
		LOG("GLEW INITIALIZED");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiContext* context =  ImGui::GetCurrentContext();
	//ImGui::NewFrame();
	//ImGui::Begin("Dear ImGui Style Editor", false);
	//ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	//ImGuiWindowFlags firstwindowflag;
	//bool* isActive = nullptr;
	//ImGui::Begin("My first tool!", isActive, firstwindowflag);
	//ImGui::Text("No puedes conmigo domingo");

	//ImGui::ShowDemoWindow();

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
