/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   29.03.2014       @details Point Sprites with 	 *
* ::::::::\ `--' /::::::::     @title  Renderer H   	         Geometry Shaders        *
*																						 *
******************************************************************************************/

#pragma once
#include "../../nclgl/OGLRenderer.h"
#include "../../nclgl/Camera.h"
#include "../../nclgl/Frustum.h"
#include <algorithm>

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	//virtual void UpdateScene(float msec);
	virtual void RenderScene();

protected:
	Camera* camera;
	Mesh*   points;
	Frustum frameFrustum;
};

