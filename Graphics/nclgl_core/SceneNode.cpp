#include "SceneNode.h"

SceneNode::SceneNode(Mesh* mesh, Vector4 colour){
	this->m_Mesh   = mesh;
	this->m_Colour = colour;
	m_Parent       = NULL;
	m_ModelScale   = Vector3(1, 1, 1);
	m_BoundingRadius = 1.0f;
	m_DistanceFromCamera = 0.0f;
}

SceneNode::~SceneNode(void){
	for (unsigned int i = 0; i < m_Children.size(); ++i)
		delete m_Children[i];
}

void SceneNode::AddChild(SceneNode* s){
	m_Children.push_back(s);
	s->m_Parent = this;
}

void SceneNode::Draw(const OGLRenderer &r) {
	if (m_Mesh)
		m_Mesh->Draw();
}

//generate correct world space transformation/node+children
void SceneNode::Update(float msec){
	if (m_Parent)
		m_WorldTransform = m_Parent->m_WorldTransform * m_LocalTransform;

	else
		m_WorldTransform = m_LocalTransform;

	for (vector<SceneNode*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i)
		(*i)->Update(msec);
}
