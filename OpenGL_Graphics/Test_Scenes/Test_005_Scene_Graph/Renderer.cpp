#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {
	CubeRobot::CreateCube();
	m_Camera = new Camera();
	currentShader = new Shader(SHADERDIR"Test_06_SceneVertex.glsl", SHADERDIR"Test_06_SceneFragment.glsl");

	if (!currentShader->LinkProgram()){
		return;
	}

	projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);

	m_Camera->SetPosition(Vector3(-100, 30, -190));
	m_Root = new SceneNode();
	m_Root->AddChild(new CubeRobot());

	glEnable(GL_DEPTH_TEST);
	init = true;
}

Renderer::~Renderer(void) {
	delete m_Root;
	CubeRobot::DeleteCube();
}

void Renderer::UpdateScene(float msec){
	m_Camera->UpdateCamera(msec);
	viewMatrix = m_Camera->BuildViewMatrix();
	m_Root->Update(msec);
}

void Renderer::RenderScene(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glUseProgram(currentShader->GetProgram());
	UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 1);
	DrawNode(m_Root);

	glUseProgram(0);
	SwapBuffers();
}

void Renderer::DrawNode(SceneNode* n){
	if (n->GetMesh()){
		Matrix4 transform = n->GetWorldTransform() * Matrix4::Scale(n->GetModelScale());

		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"), 1, false, (float*)&transform);
		glUniform4fv(glGetUniformLocation(currentShader->GetProgram(), "nodeColour"), 1, (float*)&n->GetColour());

		glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "useTexture"), (int)n->GetMesh()->GetTexture());
		n->GetMesh()->Draw();
	}

	for (vector<SceneNode*>::const_iterator i = n->GetChildIteratorStart(); i != n->GetChildIteratorEnd(); ++i){
		DrawNode(*i);
	}
}