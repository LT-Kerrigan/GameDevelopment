/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   08.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Frustum		   	@details Week_2_Tutorial_7		 *
*																						 *
******************************************************************************************/

#pragma once

#include "Plane.h"
#include "Matrix4.h"
#include "SceneNode.h"

class Matrix4;													// compile the Mat4 class first;

class Frustum {
public:
	Frustum(void) {};
	~Frustum(void) {};

	void FromMatrix(const Matrix4 &mvp);
	bool InsideFrustum(SceneNode &n);

protected:
	Plane planes[6];
};