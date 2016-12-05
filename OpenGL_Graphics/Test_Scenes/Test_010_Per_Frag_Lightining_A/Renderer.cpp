#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent){
	camera = new Camera(-30.0f, 180.0f, Vector3(0.0f, -1500.0f, 0.0f));

	heightMap = new HeightMap(TEXTUREDIR"terrain.raw");

	currentShader = new Shader(SHADERDIR"Test_11_A_PerPixelVertex.glsl", SHADERDIR"Test_11_A_PerPixelFragment.glsl");
	
	heightMap->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"BarrenReds.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	heightMap->SetBumpMap(SOIL_load_OGL_texture(TEXTUREDIR"BarrenRedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	if (!currentShader->LinkProgram() || !heightMap->GetTexture()){
		return;
	}

	SetTextureRepeating(heightMap->GetTexture(), true);
	SetTextureRepeating(heightMap->GetBumpMap(), true);

	light = new Light(Vector3((RAW_HEIGHT * HEIGHTMAP_X / 2.0f), 100.0f, (RAW_HEIGHT*HEIGHTMAP_Z / 2.0f)), Vector4(1, 1, 1, 1), (RAW_WIDTH*HEIGHTMAP_X) / 2.0f);

	projMatrix = Matrix4::Perspective(1.0f, 15000.0f, (float)width / (float)height, 45.0f);

	glEnable(GL_DEPTH_TEST);
	init = true;
}

Renderer::~Renderer(void) {
	delete camera;
	delete heightMap;
	delete light;
}

void Renderer::UpdateScene(float msec){
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();
}

void Renderer::RenderScene(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "bumpTex"), 1);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());

	UpdateShaderMatrices();
	SetShaderLight(*light);

	heightMap->Draw();

	glUseProgram(0);
	SwapBuffers();
}