#pragma once

#include <OGLRenderer.h>
#include <Camera.h>
#include <MD5Mesh.h>
#include <MD5Node.h>

#define SHADOWSIZE 2048

class Renderer : public OGLRenderer {
public:
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void UpdateScene(float msec);
	virtual void RenderScene();

protected:
	void DrawMesh();
	void DrawFloor();
	void DrawShadowScene();
	void DrawCombinedScene();

	Shader* sceneShader;
	Shader* shadowShader;

	GLuint shadowTex;
	GLuint shadowFBO;

	MD5FileData* hellData;
	MD5Node*     hellNode;
	Mesh*        floor;
	Camera*      camera;
	Light*       light;
};
