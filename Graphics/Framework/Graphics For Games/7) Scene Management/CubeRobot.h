/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   08.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  CubeRobot	   	@details Week_2_Tutorial_7		 *
*																						 *
******************************************************************************************/

#pragma once
#include "../../nclgl/SceneNode.h"
#include "../../nclgl/OBJMesh.h"

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
