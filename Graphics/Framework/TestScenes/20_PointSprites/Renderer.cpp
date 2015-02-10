/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   29.03.2014       @details Point Sprites with 	 *
* ::::::::\ `--' /::::::::     @title  Renderer    	             Geometry Shaders        *
*																						 *
******************************************************************************************/

#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
	points = Mesh::GeneratePoints(100);
	
	points->SetTexture(SOIL_load_OGL_texture("../../Textures/brick.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
	if (!points->GetTexture()) {
		return;
	}

	currentShader = new Shader(SHADERDIR"MatrixVertex.glsl", SHADERDIR"SimpleFrag.glsl", SHADERDIR"PointGeom.glsl");
	if (!currentShader->LinkProgram()) {
		return;
	}

	init = true;
	projMatrix = Matrix4::Perspective(1.0f, 500.0f, width/height, 45.0f);
}

Renderer::~Renderer(void) {
	delete points;
}

void Renderer::RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(currentShader->GetProgram());
	UpdateShaderMatrices();
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	points->Draw();
	glUseProgram(0);
	SwapBuffers();
}

