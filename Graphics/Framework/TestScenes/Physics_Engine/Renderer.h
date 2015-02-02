/******************************************************************************
- physics and AI
- It will split nodes up into those that are opaque and transparent
- render accordingly
- ability to add and remove scene nodes, 
- ability to set the camera - as these are now to be controlled by game
- singleton-like class, as with the PhysicsEngine. 
- it is created, accessed, and destroyed via static functions.
*/

#pragma once

#include "../../nclgl/OGLRenderer.h"
#include "../../nclgl/SceneNode.h"
#include "../../nclgl/Camera.h"
#include "../../nclgl/Frustum.h"
#include <algorithm>

class Renderer : public OGLRenderer	{
public:
	virtual void RenderScene();
	virtual void UpdateScene(float msec);

	void	SetCamera(Camera*c);

	void	AddNode(SceneNode* n);

	void	RemoveNode(SceneNode* n);

	//Statics
	static bool Initialise() {
		instance = new Renderer(Window::GetWindow());
		return instance->HasInitialised();
	}

	static void Destroy() {
		delete instance;
	}

	static Renderer&GetRenderer() { return *instance; }

protected:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	void	BuildNodeLists(SceneNode* from);
	void	SortNodeLists();
	void	ClearNodeLists();
	void	DrawNodes();
	void	DrawNode(SceneNode*n);

	SceneNode*	root;
	Camera*		camera;
	Shader*		simpleShader;

	Frustum		frameFrustum;

	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;

	static Renderer*	instance;
};

