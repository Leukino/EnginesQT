#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleSimp : public Module
{
public:
	ModuleSimp(Application* app, bool start_enabled = true);
	virtual ~ModuleSimp();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	Mesh LoadMesh(const char* file_path);

	Mesh tontofeo;

public:

};