#pragma once
#include "nclgl_core/OGLRenderer.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer();

	virtual void RenderScene();

	void SwitchToPerspective();
	void SwitchToOrthographic();

	inline void SetScale(float s)      { m_Scale = s; }
	inline void SetRotation(float r)   { m_Rotation = r; }
	inline void SetPosition(Vector3 p) { m_Position = p; }

protected:
	Mesh*   m_Mesh;
	float   m_Scale;
	float   m_Rotation;
	Vector3 m_Position;
};