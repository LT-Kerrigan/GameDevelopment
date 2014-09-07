/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Physics Engine		     *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   09.02.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  RigidBody    	@details Physics Engine	    	 *
*																						 *
*****************************************************************************************/

#include "Vector3.h"
#include "Matrix4.h"

class RigidBody{
public:
	Vector3 m_Position;
	Vector3 m_LinearVelocity;
	Vector3 m_Force;
	float   m_InvMass;

	Matrix4 m_Orientantion;
	Vector3 m_AngularVelocity;
	Vector3 m_Torque;
	Matrix4 m_InvInertia;
};