/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   15.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Tutorial #11		@details Advanced Programming 	 *
*																						 *
*****************************************************************************************/

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
	void DrawHeightMap();

	//Mesh*   heightMap;
	HeightMap* heightMap;
	Camera*   camera;
	Light*    light;
	Shader*   heightMapShader;
};