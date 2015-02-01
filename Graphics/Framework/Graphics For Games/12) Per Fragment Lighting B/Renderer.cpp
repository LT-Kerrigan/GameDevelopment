/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   23.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Tutorial #13		@details CubeMap			 	 *
*																						 *
*****************************************************************************************/

#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
	camera    = new Camera();
	heightMap = new HeightMap("../../Textures/HeightMapMedium.raw");
	quad      = Mesh::GenerateQuad();
	quadGrass = Mesh::GenerateQuad();

	camera->SetPosition(Vector3(RAW_WIDTH * HEIGHTMAP_X / 2.0f, 500.0f, RAW_WIDTH * HEIGHTMAP_X));

	light = new Light(Vector3(RAW_WIDTH * HEIGHTMAP_X / 2.0f, 500.0f, (RAW_HEIGHT * HEIGHTMAP_Z / 2.0f)), Vector4(0.9f, 0.9f, 1.0f, 1), (RAW_WIDTH * HEIGHTMAP_X) /*/ 2.0f*/);

	reflectShader = new Shader("../../Shaders/PerPixelVertex.glsl", "../../Shaders/ReflectFragment.glsl");
	skyboxShader  = new Shader("../../Shaders/SkyboxVertex.glsl", "../../Shaders/SkyboxFragment.glsl");
	lightShader   = new Shader("../../Shaders/PerPixelVertex.glsl", "../../Shaders/MultiTexPerPixelFragment.glsl");
	grassShader   = new Shader("../../Shaders/GrassBladeVertex.glsl", "../../Shaders/GrassBladeFragment.glsl");

	if (!reflectShader->LinkProgram() || !lightShader->LinkProgram() || !skyboxShader->LinkProgram() || !grassShader->LinkProgram()) {	
		return;
	}

	quad->SetTexture(SOIL_load_OGL_texture("../../Textures/water.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	quadGrass->SetTexture(SOIL_load_OGL_texture("../../Textures/GrassBlade.PNG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	heightMap->SetTexture(SOIL_load_OGL_texture("../../Textures/Barren Reds.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	heightMap->SetBumpMap(SOIL_load_OGL_texture("../../Textures/grass_tiled.PNG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	//heightMap->SetBumpMap(SOIL_load_OGL_texture("../../Textures/Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	cubeMap = SOIL_load_OGL_cubemap("../../../../../../ART/Skyboxes/land/lands1_front.JPG",
									"../../../../../../ART/Skyboxes/land/lands1_back.JPG",
									"../../../../../../ART/Skyboxes/land/lands1_top.JPG",
									"../../../../../../ART/Skyboxes/land/lands1_top.JPG",
									"../../../../../../ART/Skyboxes/land/lands1_left.JPG",
									"../../../../../../ART/Skyboxes/land/lands1_right.JPG",SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	if (!cubeMap || !quad->GetTexture() || !heightMap->GetTexture() || !heightMap->GetBumpMap() || !quadGrass->GetTexture()) {
		return;
	}

	SetTextureRepeating(quad->GetTexture(), true);
	SetTextureRepeating(quadGrass->GetTexture(), true);
	SetTextureRepeating(heightMap->GetTexture(), true);
	SetTextureRepeating(heightMap->GetBumpMap(), true);

	init        = true;
	waterRotate = 0.0f;

	projMatrix = Matrix4::Perspective(1.0f, 15000.0f, (float)width / (float)height, 45.0f);

	quadGrass->SetRandomPositions(10000, 50.0f, 4096.0f * 4);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

Renderer::~Renderer(void){
	delete camera;
	delete heightMap;
	delete quad;
	delete quadGrass;
	delete reflectShader;
	delete skyboxShader;
	delete lightShader;
	delete grassShader;
	delete light;
	currentShader = 0;
}

void Renderer::UpdateScene(float msec){
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();
	waterRotate += msec / 1000.0f;
}

float xoff, zoff;
void Renderer::RenderScene(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	DrawSkybox();
	DrawHeightmap();
	DrawWater();

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_1)) xoff += 10.0f;
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_2)) xoff -= 10.0f;
	DrawGrass(xoff, zoff);

	SwapBuffers();
}

void Renderer::DrawSkybox(){
	glDepthMask(GL_FALSE);
	SetCurrentShader(skyboxShader);

	UpdateShaderMatrices();
	quad->Draw();

	glUseProgram(0);
	glDepthMask(GL_TRUE);
}

void Renderer::DrawHeightmap(){
	SetCurrentShader(lightShader);
	SetShaderLight(*light);

	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	//glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "bumpTex"), 1);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseGrassTex"), 1);

	modelMatrix.ToIdentity();
	textureMatrix.ToIdentity();

	UpdateShaderMatrices();

	heightMap->Draw();

	glUseProgram(0);
}

void Renderer::DrawWater(){
	SetCurrentShader(reflectShader);
	SetShaderLight(*light);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "cubeTex"), 2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	float heightX = (RAW_WIDTH * HEIGHTMAP_X / 2.0f);
	float heightY = 256 * HEIGHTMAP_Y / 10.0f;//3.0f;
	float heightZ = (RAW_HEIGHT * HEIGHTMAP_Z / 2.0f);

	modelMatrix = Matrix4::Translation(Vector3(heightX, heightY, heightZ)) * Matrix4::Scale(Vector3(heightX, 1, heightZ)) * Matrix4::Rotation(90, Vector3(1.0f, 0.0f, 0.0f));

	textureMatrix = Matrix4::Scale(Vector3(10.0f, 10.0f, 10.0f)) * Matrix4::Rotation(waterRotate, Vector3(0.0f, 0.0f, 1.0f));

	UpdateShaderMatrices();

	quad->Draw();

	glUseProgram(0);
}

void Renderer::DrawGrass(float xoff, float zoff) {
	SetCurrentShader(grassShader);
	//SetCurrentShader(lightShader);
	SetShaderLight(*light);

	glUniform3fv(glGetUniformLocation(grassShader->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());
	glUniform1i(glGetUniformLocation(grassShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(grassShader->GetProgram(), "vertexTexture"), 3);
	glUniform3f(glGetUniformLocation(grassShader->GetProgram(), "vertexHeight"), HEIGHTMAP_X * RAW_WIDTH, HEIGHTMAP_Y, HEIGHTMAP_Z * RAW_HEIGHT);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, heightMap->vertexTexture);

	//glActiveTexture(GL_TEXTURE3);
	//glBindTexture(GL_TEXTURE_2D, heightMap->GetTexture());
	 
	float heightX = (RAW_WIDTH * HEIGHTMAP_X / 2.0f);
	float heightY = 256 * HEIGHTMAP_Y / 10.0f;//3.0f;
	float heightZ = (RAW_HEIGHT * HEIGHTMAP_Z / 2.0f);

	textureMatrix.ToIdentity();
	modelMatrix.ToIdentity();

	modelMatrix = Matrix4::Translation(Vector3(xoff, 0.0f,zoff)) * Matrix4::Scale(Vector3(50.0f, 50.0f, 50.0f));
	
	UpdateShaderMatrices();
	//quadGrass->Draw();
	quadGrass->DrawInstance(10000);
	glUseProgram(0);
}



