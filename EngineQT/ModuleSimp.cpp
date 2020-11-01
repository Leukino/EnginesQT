#include "Globals.h"
#include "Application.h"
#include "ModuleSimp.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/Importer.hpp"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include <iostream>


struct Mesh;
ModuleSimp::ModuleSimp(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSimp::~ModuleSimp()
{}

// Load assets
bool ModuleSimp::Start()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
	aiLogStream();
	
	//LoadMesh("assets/models/warrior/warrior.FBX");

	return true;
}

// Unload assets
bool ModuleSimp::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}

// Update: draw background
update_status ModuleSimp::Update(float dt)
{
	return UPDATE_CONTINUE;
}

Mesh ModuleSimp::LoadMesh(const char* file_path)
{
	Mesh myMesh;
	LOG("Attempt to load mesh in %s \n", file_path);
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		aiReleaseImport(scene);
		LOG("Opened scene POGGERS");
	}
	else {
		LOG(aiGetErrorString());
		return myMesh;
	}
	
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		//iterate meshes in scene
		myMesh.num_vertex = scene->mMeshes[i]->mNumVertices;
		myMesh.vertex = new float[myMesh.num_vertex * 3];
		memcpy(myMesh.vertex, scene->mMeshes[i]->mVertices, sizeof(float) * myMesh.num_vertex* 3);
		myMesh.num_index = scene->mMeshes[i]->mNumFaces;
		if (scene->mMeshes[i]->HasFaces())
		{
			myMesh.num_index = scene->mMeshes[i]->mNumFaces * 3;
			myMesh.index = new uint[myMesh.num_index];
			for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
			{
				if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
				{
					LOG("WARNING, geometery face with != 3 indices!");
				}
				else
				{
					memcpy(&myMesh.index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
				}
			}
		}
		
	}
	LOG("Number of meshes in scene %d", scene->mNumMeshes);

	LOG("Current mesh characteristics: Total Vertices %d\n, Total Indices %d", myMesh.num_vertex, myMesh.num_index);
	return myMesh;
};