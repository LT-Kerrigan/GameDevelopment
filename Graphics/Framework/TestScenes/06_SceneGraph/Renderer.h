/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   01.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Render CLASS   	@details Tutorial_6_Week_2		 *
*																						 *
******************************************************************************************/

#pragma once
#include "../../GraphicsFramework/OGLRenderer.h"
#include "../../GraphicsFramework/SceneNode.h"
#include "../../GraphicsFramework/Camera.h"
#include "CubeRobot.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void UpdateScene(float msec);
	virtual void RenderScene();

protected:
	void DrawNode(SceneNode*n);
	SceneNode* root;
	Camera* camera;
};
