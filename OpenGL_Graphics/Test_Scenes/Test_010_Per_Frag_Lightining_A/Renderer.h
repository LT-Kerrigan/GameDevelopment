#pragma once

#include <OGLRenderer.h>
#include <Camera.h>
#include <HeightMap.h>

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	void DrawHeightMap();

	//Mesh*   heightMap;
	HeightMap* heightMap;
	Camera*   camera;
	Light*    light;
	Shader*   heightMapShader;
};