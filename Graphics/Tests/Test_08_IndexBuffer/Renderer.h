#pragma once

#include "nclgl_core/OGLRenderer.h"
#include "nclgl_core/Camera.h"
#include "nclgl_core/HeightMap.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	HeightMap* heightMap;
	Camera*    camera;
};