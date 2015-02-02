/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   08.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Plane		   	@details Week_2_Tutorial_7		 *
*																						 *
******************************************************************************************/

#include "Plane.h"

Plane::Plane(const Vector3 &normal, float distance, bool normalise){
	if (normalise){
		float length = sqrt(Vector3::Dot(normal, normal));
		this->normal = normal / length;
		this->distance = distance / length;
	}
	else {
		this->normal   = normal;
		this->distance = distance;
	}
}

bool Plane::SphereInPlane(const Vector3 &position, float radius) const {
	if (Vector3::Dot(position, normal) + distance <= -radius){
		return false;
	}
	return true;
}