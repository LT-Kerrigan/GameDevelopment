#pragma once

#include <OGLRenderer.h>
#include <HeightMap.h>
#include <Camera.h>

#define POST_PASSES 10

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	void PresentScene();
	void DrawPostProcess();
	void DrawScene();

	void DrawDebugTexture();

	Shader*    sceneShader;
	Shader*    combineShader;
	Camera*    camera;
	Mesh*      quad;
	Mesh*	   quad_corner;
	HeightMap* heightMap;

	GLuint bufferFBO;
	GLuint processFBO;
	GLuint bufferColourTex[2];
	GLuint bufferDepthTex;

	GLuint debugbufferFBO;
	GLuint debugColorTex;
	GLuint debugdepthTex;
};