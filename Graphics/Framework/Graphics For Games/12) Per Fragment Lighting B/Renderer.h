/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   23.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Tutorial #14		@details CubeMap			 	 *
*																						 *
*****************************************************************************************/

#pragma once

#include "../../nclgl/OGLRenderer.h"
#include "../../nclgl/Camera.h"
#include "../../nclgl/HeightMap.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	void DrawHeightmap();
	void DrawWater();
	void DrawGrass(float xoff, float zoff);
	void DrawSkybox();

	Shader* lightShader;
	Shader* reflectShader;
	Shader*	grassShader;
	Shader* skyboxShader;

	HeightMap* heightMap;
	Mesh*      quad;
	Mesh*      quadGrass;
	Light*     light;
	Camera*    camera;

	GLuint     cubeMap;
	float      waterRotate;
};