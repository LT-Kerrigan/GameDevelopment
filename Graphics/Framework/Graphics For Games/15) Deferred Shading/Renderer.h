/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   26.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Tutorial #15		@details Deferred Rendering		 *
*																						 *
*****************************************************************************************/

#pragma once

#include "../../nclgl/OGLRenderer.h"
#include "../../nclgl/Camera.h"
#include "../../nclgl/OBJMesh.h"
#include "../../nclgl/HeightMap.h"

#define LIGHTNUM 8 

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	void FillBuffers();
	void DrawPointLights();
	void CombineBuffers();
	void GenerateScreenTexture(GLuint &into, bool depth = false);

	Shader* sceneShader;
	Shader* pointlightShader;
	Shader* combineShader;

	Light*   pointLights;
	Mesh*    heightMap;
	OBJMesh* sphere;
	Mesh*    quad;
	Camera*  camera;

	float rotation;

	GLuint bufferFBO;
	GLuint bufferColourTex;
	GLuint bufferNormalTex;
	GLuint bufferDepthTex;

	GLuint pointLightFBO;
	GLuint lightEmissiveTex;
	GLuint lightSpecularTex;
};

