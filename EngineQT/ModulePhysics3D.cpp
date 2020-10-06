#include "Globals.h"
#include "Application.h"
#include "ModulePhysics3D.h"
#include "Primitive.h"

ModulePhysics3D::ModulePhysics3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModulePhysics3D::~ModulePhysics3D()
{
}

// Render not available yet----------------------------------
bool ModulePhysics3D::Init()
{
	bool ret = true;
	return ret;
}

// ---------------------------------------------------------
bool ModulePhysics3D::Start()
{
	return true;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::Update(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics3D::CleanUp()
{
	return true;
}

// ---------------------------------------------------------

// ---------------------------------------------------------

// ---------------------------------------------------------

// ---------------------------------------------------------

// ---------------------------------------------------------

// =============================================
//void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
//{
//	line.origin.Set(from.getX(), from.getY(), from.getZ());
//	line.destination.Set(to.getX(), to.getY(), to.getZ());
//	line.color.Set(color.getX(), color.getY(), color.getZ());
//	line.Render();
//}

//void DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
//{
//	point.transform.translate(PointOnB.getX(), PointOnB.getY(), PointOnB.getZ());
//	point.color.Set(color.getX(), color.getY(), color.getZ());
//	point.Render();
//}
