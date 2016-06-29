#pragma once
#include "nclgl_core/OGLRenderer.h"
#include "nclgl_core/SceneNode.h"
#include "nclgl_core/Camera.h"
#include "nclgl_core/CubeRobot.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void UpdateScene(float msec);
	virtual void RenderScene();

protected:
	void DrawNode(SceneNode*n);
	SceneNode* m_Root;
	Camera* m_Camera;
};