#pragma once
#include <OGLRenderer.h>
#include <SceneNode.h>
#include <Camera.h>
#include <Frustum.h>
#include <CubeRobot.h>
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