#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
	m_Mesh = Mesh::GenerateTriangle();
	
	GLuint tex = SOIL_load_OGL_texture(TEXTUREDIR"brick.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	m_Mesh->SetTexture(tex);
	
	if (!m_Mesh->GetTexture()) {
		return;
	}

	currentShader = new Shader(SHADERDIR"Test_03_TexturedVertex.glsl", SHADERDIR"Test_03_TexturedFragment.glsl");
	
	if (!currentShader->LinkProgram()) {
		return;
	}

	init = true;

	projMatrix = Matrix4::Orthographic(-1, 1, 1, -1, 1, -1);

	m_Filtering = true;
	m_Repeating = false;
}

Renderer::~Renderer() {
	delete m_Mesh;
}


void Renderer::RenderScene() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());

	UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	
	m_Mesh->Draw();

	glUseProgram(0);

	SwapBuffers();
}

void Renderer::UpdateTextureMatrix(float value) {
	Matrix4 pushPos  = Matrix4::Translation(Vector3(0.5f, 0.5f, 0));
	Matrix4 popPos   = Matrix4::Translation(Vector3(-0.5f, -0.5f, 0));
	Matrix4 rotation = Matrix4::Rotation(value, Vector3(0, 0, 1));
	textureMatrix    = pushPos* rotation * popPos;
}

void Renderer::ToggleRepeating() {
	m_Repeating = !m_Repeating;
	glBindTexture(GL_TEXTURE_2D, m_Mesh->GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_Repeating ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_Repeating ? GL_REPEAT : GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::ToggleFiltering() {
	m_Filtering = !m_Filtering;
	glBindTexture(GL_TEXTURE_2D, m_Mesh->GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Filtering ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Filtering ? GL_LINEAR : GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//void Renderer::UpdateScene(float msec) {
//	m_Camera->UpdateCamera(msec);
//	viewMatrix = m_Camera->BuildViewMatrix();
//}