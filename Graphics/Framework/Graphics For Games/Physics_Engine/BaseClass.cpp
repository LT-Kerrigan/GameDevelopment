/***********************************************************************************************
*	          .--.																		       *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Physics            *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 28.09.2014	       *
*	::::::-:.`'..`'.:-::::::			@link								                   *
*	::::::::\ `--' /::::::::			@detail	BaseClass implementation					   *
************************************************************************************************/

#include "BaseClass.h"

BaseClass* BaseClass::instance = NULL;

BaseClass::BaseClass()	{
	renderCounter = 0.0f;
	physicsCounter = 0.0f;

	instance = this;
}

BaseClass::~BaseClass(void)	{
	for (vector<GameEntity*>::iterator i = allEntities.begin(); i != allEntities.end(); ++i) {
		delete (*i);
	}
	delete gameCamera;
}

void BaseClass::UpdateCore(float msec) {
	renderCounter -= msec;
	physicsCounter += msec;

	if (renderCounter <= 0.0f) {	//Update our rendering logic
		Renderer::GetRenderer().UpdateScene(1000.0f / (float)RENDER_HZ);
		Renderer::GetRenderer().RenderScene();
		renderCounter += (1000.0f / (float)RENDER_HZ);
	}

	while (physicsCounter >= 0.0f) {
		physicsCounter -= PHYSICS_TIMESTEP;
		PhysicsEngine::GetPhysicsSystem().Update(PHYSICS_TIMESTEP);
	}

	Renderer::GetRenderer().UpdateScene(msec);
	Renderer::GetRenderer().RenderScene();
}