/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   08.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Render CLASS   	@details Tutorial_8_Week_2		 *
*																						 *
******************************************************************************************/

#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
	heightMap = new HeightMap("../../Textures/terrain.raw");
	camera = new Camera(-30.0f, 180.0f, Vector3(0.0f, 500.0f, 0.0f));

	currentShader = new Shader("../../Shaders/TexturedVertex.glsl", "../../Shaders/TexturedFragment.glsl");

	if (!currentShader->LinkProgram()){
		return;
	}

	heightMap->SetTexture(SOIL_load_OGL_texture("../../Textures/Barren Reds.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	if (!heightMap->GetTexture()){
		return;
	}

	SetTextureRepeating(heightMap->GetTexture(), true);

	projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width/(float)height, 45.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	init = true;
}

Renderer::~Renderer(void){
	delete heightMap;
	delete camera;
}

void Renderer::UpdateScene(float msec){
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();
}

void Renderer::RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(currentShader->GetProgram());
	UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	heightMap->Draw();
	glUseProgram(0);
	SwapBuffers();
}