/*******************************************************************************************
*	          .--.																		   *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Graphics       *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 23.08.2014	   *
*	::::::-:.`'..`'.:-::::::			@link								               *
*	::::::::\ `--' /::::::::			@detail	Renderer header	- testing post processing. *
*																						   *
********************************************************************************************/

#pragma once

#include "../../GraphicsFramework/OGLRenderer.h"
#include "../../GraphicsFramework/HeightMap.h"
#include "../../GraphicsFramework/Camera.h"

#define POST_PASSES 10

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	void PresentScene();
	void DrawPostProcess();
	void DrawScene();

	Shader*    sceneShader;
	Shader*    combineShader;
	Camera*    camera;
	Mesh*      quad;
	HeightMap* heightMap;

	GLuint bufferFBO;
	GLuint processFBO;
	GLuint bufferColourTex[2];
	GLuint bufferDepthTex;
};