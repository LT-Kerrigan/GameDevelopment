#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
	m_Mesh = Mesh::GenerateTriangle();

	currentShader = new Shader(SHADERDIR"Test_02_MatrixVertex.glsl", SHADERDIR"Test_01_BasicFragment.glsl");

	m_Camera = new Camera();

	if (!currentShader->LinkProgram()) {
		return;
	}

	init = true;

	SwitchToOrthographic();
}

Renderer::~Renderer() {
	delete m_Mesh;
}

void Renderer::SwitchToPerspective() {
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);
}

void Renderer::SwitchToOrthographic() {
	projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, width / 2.0f, -width / 2.0f, height / 2.0f, -height / 2.0f);
}

void Renderer::RenderScene() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());

	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "projMatrix"), 1, false, (float*)&projMatrix);
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "viewMatrix"), 1, false, (float*)&viewMatrix);

	for (int i = 0; i < 3; ++i) {
		Vector3 tempPos = m_Position;
		tempPos.z += (i * 500.0f);
		tempPos.x -= (i*100.0f);
		tempPos.y -= (i*100.0f);

		modelMatrix = Matrix4::Translation(tempPos) * Matrix4::Rotation(m_Rotation, Vector3(0, 1, 0)) * Matrix4::Scale(Vector3(m_Scale, m_Scale, m_Scale));

		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"), 1, false, (float*)&modelMatrix);
		m_Mesh->Draw();
	}

	glUseProgram(0);

	SwapBuffers();
}

void Renderer::UpdateScene(float msec) {
	m_Camera->UpdateCamera(msec);
	viewMatrix = m_Camera->BuildViewMatrix();
}