#pragma once
#include "../../Engine/OGLRenderer.h"
#include "../../Engine/Camera.h"
#include "../../Engine/OBJMesh.h"
#include "../../Engine/Vector3.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer();

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

	void UpdateTextureMatrix(float rotation);
	void ToggleRepeating();
	void ToggleFiltering();

protected:
	Mesh*   m_Mesh;
	bool    m_Filtering;
	bool	m_Repeating;
	Camera*    camera;
}; 
