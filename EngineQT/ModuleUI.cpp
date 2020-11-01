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
 
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	//ImGui::StyleColorsClassic();
	ImGui::StyleColorsDark();

	MainMenuBar();

	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //SDL_GL_SwapWindow(App->window->window);

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

void ModuleUI::MainMenuBar()
{

	static const char* items[]{ "Window", "Fullscreen borderless", "Fullscreen" };
	static int selectedItem = 0;
	
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			
			if (ImGui::BeginMenu("New")) 
			{
				if (ImGui::MenuItem("New File", "Ctrl + N")) 
				{
				}

				ImGui::EndMenu();
			}
			ImGui::Spacing();
			if (ImGui::BeginMenu("Load File")) 
			{
				if (ImGui::MenuItem("Load File", "Ctrl + A"))
				{
				}

				ImGui::EndMenu();
			}
			
			ImGui::Separator();
			ImGui::Spacing();
			if (ImGui::MenuItem("Exit", "ESC")) 
			{ 

			}
			ImGui::EndMenu();
		}
		ImGui::Spacing();

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::EndMenu();
		}
		ImGui::Spacing();

		if (ImGui::MenuItem("View"))
		{

		}
		ImGui::Spacing();

		if (ImGui::BeginMenu("Settings"))
		{
			if (ImGui::MenuItem("App settings"))
			{
				specMenu = !specMenu;
			}
			ImGui::EndMenu();
		}
		ImGui::Spacing();

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("GitHub"))
			{
				ShellExecuteA(NULL, "open", "https://github.com/Leukino/EnginesQT", NULL, NULL, SW_SHOWMAXIMIZED);
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	if (specMenu)
	{
		ImGui::Begin("Settings", 0, ImGuiWindowFlags_NoResize);
		
		ImGui::Combo("Screen Resolution", &selectedItem, items, IM_ARRAYSIZE(items), 1);
		if (selectedItem == 2)
			App->window->SetFullscreen(true);
		else
			App->window->SetFullscreen(false);
		
		ImGui::Spacing();

		ImGui::Text("MinFPS");
		ImGui::SameLine();
		ImGui::SliderInt(" MaxFPS", &fps, 0, 240);
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("CPU cores: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.47f, 1.0f), "%d", App->cpuCores);

		ImGui::Text("RAM: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.47f, 1.0f), "%d gb", App->systemRAM);

		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("Graphic card: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.47f, 1.0f), "%s", App->rendererChar);

		ImGui::Text("Vendor: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.47f, 1.0f), "%s", App->vendorChar);

		ImGui::Text("Graphic card features: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.47f, 1.0f), "%s%s%s%s%s%s%s%s", (App->RDTSC) ? "RDTSC " : "", (App->MMX) ? "MMX " : "", (App->SSE) ? "SSE " : "", (App->SSE2) ? "SSE2 " : "", (App->SSE3) ? "SSE3 " : "", (App->SSE41) ? "SSE41 " : "", (App->SSE42) ? "SSE42 " : "", (App->AVX) ? "AVX " : "");	

		ImGui::End();
	}
}

