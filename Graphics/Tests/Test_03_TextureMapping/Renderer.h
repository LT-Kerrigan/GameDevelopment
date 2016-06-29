#pragma once
#include "nclgl_core/OGLRenderer.h"
#include "nclgl_core/Camera.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer();

	virtual void RenderScene();

	void UpdateTextureMatrix(float rotation);
	void ToggleRepeating();
	void ToggleFiltering();

protected:	
	Mesh*   m_Mesh;
	bool    m_Filtering;
	bool	m_Repeating;
};