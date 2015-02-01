/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   08.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Frustum		   	@details Week_2_Tutorial_7		 *
*																						 *
******************************************************************************************/

#include "Frustum.h"

bool Frustum::InsideFrustum(SceneNode &n) {
	for (int p = 0; p < 6; ++p){
		if (!planes[p].SphereInPlane(n.GetWorldTransform().GetPositionVector(), 
			n.GetBoundingRadius())){
			return false;																//scenenode is outside plane
		}
	}
	return true;																		//scenenode appears in every plane
}

void Frustum::FromMatrix(const Matrix4 &mat) {
	Vector3 xaxis = Vector3(mat.values[0], mat.values[4], mat.values[8]);
	Vector3 yaxis = Vector3(mat.values[1], mat.values[5], mat.values[9]);
	Vector3 zaxis = Vector3(mat.values[2], mat.values[6], mat.values[10]);
	Vector3 waxis = Vector3(mat.values[3], mat.values[7], mat.values[11]);
	
	planes[0] = Plane(waxis - xaxis, (mat.values[15] - mat.values[12]), true);			//Right
	planes[1] = Plane(waxis + xaxis, (mat.values[15] + mat.values[12]), true);			//Left
	planes[2] = Plane(waxis + yaxis, (mat.values[15] + mat.values[13]), true);			//Bottom
	planes[3] = Plane(waxis - yaxis, (mat.values[15] - mat.values[13]), true);			//Top
	planes[4] = Plane(waxis - zaxis, (mat.values[15] - mat.values[14]), true);			//Far
	planes[5] = Plane(waxis + zaxis, (mat.values[15] + mat.values[14]), true);			//Near
}