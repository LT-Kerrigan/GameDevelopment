#pragma once
#include <OGLRenderer.h>
#include <SceneNode.h>
#include <Camera.h>
#include <CubeRobot.h>

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