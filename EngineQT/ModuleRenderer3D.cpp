#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "SDL\include\SDL_opengl.h"

#include <gl/glew.h>

#include <gl/GL.h>
#include <gl/GLU.h>

#include "glew/include/GL/glew.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */



ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;
	
	//Create context

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	context = SDL_GL_CreateContext(App->window->window);
	if (GLEW_OK != glewInit())
	{
		LOG("GLEW WENT BRRR");
	}
	else
		LOG("GLEW INITIALIZED");

	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, context);
	ImGui_ImplOpenGL3_Init("#version 330");
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);

		//glEnable(GL_TEXTURE_2D);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());	

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	draw();
	//todo draw things :)

	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f); //fov :O
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void ModuleRenderer3D::draw() 
{
	glLineWidth(2.0f);
	glBegin(GL_TRIANGLES);
	//GLfloat vertices[] =
	//{
	//	1.0f, 1.0f, 1.0f,
	//	0.0f, 1.0f, 1.0f,
	//	0.0f, 0.0f, 1.0f
	//};

	GLfloat Vertices[] = {
	-0.8f, -0.8f, 0.0f, 1.0f,
	 0.0f,  0.8f, 0.0f, 1.0f,
	 0.8f, -0.8f, 0.0f, 1.0f
	};

	GLubyte indices[] = {
		0, 1, 2, 2, 3, 0
	};

	uint my_id = 0;
	glGenBuffers(1, (GLuint*) & (my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 3, Vertices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, Vertices);
	
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	//glDrawRangeElements(GL_TRIANGLES, 0, 3, 6, GL_UNSIGNED_BYTE, indices);



	glDisableClientState(GL_VERTEX_ARRAY);

	//glVertex3f(1.0f, 1.0f, 1.0f);    // v0-v1-v2
	//glVertex3f(0.0f, 1.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, 1.0f);
	
	//glVertex3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, 1.0f); 
	//glVertex3f(1.0f, 0.0f, 1.0f);	// v2-v3-v0

	//// right face =================
	//glVertex3f(v0);    // v0-v3-v4
	//glVertex3f(v3);
	//glVertex3f(v4);

	//glVertex3f(v4);    // v4-v5-v0
	//glVertex3f(v5);
	//glVertex3f(v0);

	//// top face ===================
	//glVertex3f(v0);    // v0-v5-v6
	//glVertex3f(v5);
	//glVertex3f(v6);

	//glVertex3f(v6);    // v6-v1-v0
	//glVertex3f(v1);
	//glVertex3f(v0);


	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 10.0f, 0.0f);


	glEnd();
	return;
}