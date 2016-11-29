#pragma once
#include <OGLRenderer.h>
#include <Camera.h>

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