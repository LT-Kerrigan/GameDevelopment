#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
	m_TriangleMesh = Mesh::GenerateTriangle();

	currentShader = new Shader(SHADERDIR"Test_01_BasicVertex.glsl",
		SHADERDIR"Test_01_BasicFragment.glsl");

	if (!currentShader->LinkProgram()) {
		return;
	}

	init = true;
}
Renderer::~Renderer(void) {
	delete m_TriangleMesh;
}

void Renderer::RenderScene() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(currentShader->GetProgram());
	m_TriangleMesh->Draw();
	glUseProgram(0);

	SwapBuffers();
}

