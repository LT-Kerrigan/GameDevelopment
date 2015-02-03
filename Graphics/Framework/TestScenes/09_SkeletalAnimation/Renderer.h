/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   14.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Render CLASS   	@details Tutorial_9_Week_2		 *
*																						 *
******************************************************************************************/

#pragma once
#include "../../GraphicsFramework/OGLRenderer.h"
#include "../../GraphicsFramework/Camera.h"
#include "../../GraphicsFramework/MD5Mesh.h"

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

