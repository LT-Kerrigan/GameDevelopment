#pragma once

#include <OGLRenderer.h>
#include <Mesh.h>
#include <camera.h>

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

	/*
	Transforms a world space position into screen coordinates
	*/
	Vector3	WorldPosToScreenPos(Vector3 screenPos);

protected:
	Mesh*	triangle;	
	Mesh*	quad;		
	Camera* camera;		
};

