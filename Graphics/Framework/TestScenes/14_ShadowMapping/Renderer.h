/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   25.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Tutorial #14		@details ShadowMap			 	 *
*																						 *
*****************************************************************************************/

#pragma once

#include "../../GraphicsFramework/OGLRenderer.h"
#include "../../GraphicsFramework/Camera.h"
#include "../../GraphicsFramework/MD5Mesh.h"
#include "../../GraphicsFramework/MD5Node.h"

#define SHADOWSIZE 2048

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void UpdateScene(float msec);
	virtual void RenderScene();

protected:
	void DrawMesh();
	void DrawFloor();
	void DrawShadowScene();
	void DrawCombinedScene();

	Shader* sceneShader;
	Shader* shadowShader;

	GLuint shadowTex;
	GLuint shadowFBO;

	MD5FileData* hellData;
	MD5Node*     hellNode;
	Mesh*        floor;
	Camera*      camera;
	Light*       light;
};
