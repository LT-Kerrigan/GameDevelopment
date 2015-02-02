/***********************************************************************************************
*	          .--.																		       *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Physics            *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 28.09.2014	       *
*	::::::-:.`'..`'.:-::::::			@link								                   *
*	::::::::\ `--' /::::::::			@detail	performs updates (rendering, physics, sound);  *
*										        holds all scene entities (classes / game obj); *
*										        camera looks at subsystems                     *
************************************************************************************************/

#pragma once
#include "Renderer.h"
#include "PhysicsEngine.h"
#include "GameEntity.h"
#include "../../nclgl/Camera.h"
#include <vector>

#define RENDER_HZ	60
#define PHYSICS_HZ	120
#define PHYSICS_TIMESTEP (1000.0f / (float)PHYSICS_HZ)

class BaseClass	{
public:
	BaseClass();
	~BaseClass(void);

	virtual void UpdateCore(float msec);

	virtual void UpdateGame(float msec) = 0;

	static BaseClass& GetBaseClass() { return *instance; }

protected:
	float renderCounter;
	float physicsCounter;

	vector<GameEntity*> allEntities;

	Camera* gameCamera;
	static BaseClass* instance;
};