/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   08.03.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Plane		   	@details Week_2_Tutorial_7		 *
*																						 *
******************************************************************************************/

#pragma once
#include "Vector3.h"

class Plane {
public:
	Plane(void){};
	Plane(const Vector3 &normal, float distance, bool normalise = false);
	~Plane(void){};

	void SetNormal(const Vector3 &normal) { this->normal = normal; }
	Vector3 GetNormal() const             { return normal; }

	void SetDistance(float dist) { distance = dist; }
	float GetDistance() const    { return distance; }

	bool SphereInPlane(const Vector3 &position, float radius) const;

protected:
	Vector3 normal;
	float distance;
};