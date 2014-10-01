/*
- setting up the game;
- environment (level, enemies, pickups, whatever);
- keeping track of what the gameplay state;
- game object loading would be handled by config files 
- really useful for debugging  (drawing debug bounding volumes to see when objects collide);
*/

#pragma once
#include "GameEntity.h"
#include "BaseClass.h"
#include "../../nclgl/OGLRenderer.h"
#include "../../nclgl/CubeRobot.h"

class TestEngine : public BaseClass	{
public:
	TestEngine();
	~TestEngine(void);

	virtual void UpdateGame(float msec);

protected:
	GameEntity* BuildRobotEntity();

	GameEntity* BuildCubeEntity(float size);

	GameEntity* BuildSphereEntity(float radius);

	GameEntity* BuildQuadEntity(float size);


	Mesh* cube;
	Mesh* quad;
	Mesh* sphere;
};

