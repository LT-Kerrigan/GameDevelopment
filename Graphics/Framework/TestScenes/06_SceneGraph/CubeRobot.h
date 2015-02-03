/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   02.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  CubeRobot	   	@details Week_2_Tutorial_6		 *
*																						 *
******************************************************************************************/

#pragma once
#include "../../GraphicsFramework/SceneNode.h"
#include "../../GraphicsFramework/OBJMesh.h"

class CubeRobot : public SceneNode {
public:
	CubeRobot(void);
	~CubeRobot(void){};
	virtual void Update(float msec);

	static void CreateCube() {
		OBJMesh*m = new OBJMesh();
		m->LoadOBJMesh("../../Meshes/cube.obj");
		cube = m;
	}
	static void DeleteCube(){ delete cube; }

protected:
	static Mesh* cube;
	SceneNode* head;
	SceneNode* leftArm;
	SceneNode* rightArm;
};
