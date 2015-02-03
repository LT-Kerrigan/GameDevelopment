/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   08.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Render CLASS   	@details Tutorial_8_Week_2		 *
*																						 *
******************************************************************************************/

#pragma once

#include "../../GraphicsFramework/OGLRenderer.h"
#include "../../GraphicsFramework/Camera.h"
#include "../../GraphicsFramework/HeightMap.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	HeightMap* heightMap;
	Camera* camera;
};