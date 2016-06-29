#pragma once
#include "nclgl_core/OGLRenderer.h"
#include "nclgl_core/Camera.h"
#include "nclgl_core/MD5Mesh.h"

class Renderer : public OGLRenderer{
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);
	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	MD5FileData* hellData;
	MD5Node*     hellNode;
	Camera*      camera;
};