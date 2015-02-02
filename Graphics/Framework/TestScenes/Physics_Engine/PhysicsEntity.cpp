/***********************************************************************************************
*	          .--.																		       *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Physics            *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 28.09.2014	       *
*	::::::-:.`'..`'.:-::::::			@link								                   *
*	::::::::\ `--' /::::::::			@detail	Physics Entity implementation with hook vertex *
*																						       *
************************************************************************************************/

#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(void)	{
	target = NULL;
}

PhysicsEntity::PhysicsEntity(Quaternion orientation, Vector3 position) {
	m_orientation = orientation;
	m_position = position;
}

PhysicsEntity::~PhysicsEntity(void)	{

}

void PhysicsEntity::Update(float msec) {
	
	//Simplex Euler
	m_linearVelocity += m_linearVelocity + m_acceleration * msec;
    m_position       += m_position + m_linearVelocity * msec;

	m_linearVelocity = m_linearVelocity * m_DampThreshold;

	if (m_linearVelocity.x < MINIMUM_VELOCITY || m_linearVelocity.y < MINIMUM_VELOCITY || m_linearVelocity.z < MINIMUM_VELOCITY) {
		m_linearVelocity.ToZero();
	}
	
	if (target) {
		target->SetTransform(BuildTransform());
	}
}

/*
This function simply turns the orientation and position
of our physics node into a transformation matrix, suitable
for plugging into our Renderer!
*/
Matrix4 PhysicsEntity::BuildTransform() {
	Matrix4 m = m_orientation.ToMatrix();

	m.SetPositionVector(m_position);

	return m;
}