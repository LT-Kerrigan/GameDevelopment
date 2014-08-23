/*******************************************************************************************
*	          .--.																		   *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Graphics       *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 23.08.2014	   *
*	::::::-:.`'..`'.:-::::::			@link								               *
*	::::::::\ `--' /::::::::			@detail	Renderer header	- testing proj. vs ortho.  *
*																						   *
********************************************************************************************/

#pragma once
#include "./nclgl/OGLRenderer.h"

class Renderer : public OGLRenderer {
	Renderer(Window &parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	
	void SwitchToPerspective();
	void SwitchToOrthographic();

	inline void SetScale(float s)      { scale = s; }
	inline void SetRotation(float r)   { rotation = r; }
	inline void SetPosition(Vector3 p) { position = p; }

protected:
	Mesh* triangle;
	//Camera* camera;
	float scale;
	float rotation;
	Vector3 position;
	//float speed;
};