#pragma once
#include "nclgl_core/OGLRenderer.h"
#include "nclgl_core/SceneNode.h"
#include "nclgl_core/Camera.h"
#include "nclgl_core/Frustum.h"
#include "nclgl_core/CubeRobot.h"
#include <algorithm>

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void UpdateScene(float msec);
	virtual void RenderScene();

protected:
	void BuildNodeLists(SceneNode* from);
	void SortNodeLists();
	void ClearNodeLists();
	void DrawNodes();
	void DrawNode(SceneNode*n);

	SceneNode* root;
	Camera*    camera;
	Mesh*      quad;
	Mesh*	   triangle;
	Frustum    frameFrustum;

	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;
};