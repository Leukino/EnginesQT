#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

struct Mesh
{
	uint id_index = 0;
	uint num_index = 0;
	uint id_vertex = 0;
	uint num_vertex = 0;

	uint* index = nullptr;
	float* vertex = nullptr;
};

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	void draw();
	bool CleanUp();

	void OnResize(int width, int height);
	Mesh myloadedmesh;
public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	
};