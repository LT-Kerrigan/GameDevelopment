/***********************************************************************************************
*	          .--.																		       *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Physics            *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 28.09.2014	       *
*	::::::-:.`'..`'.:-::::::			@link								                   *
*	::::::::\ `--' /::::::::			@detail	Physics Entity implementation with hook vertex *
*																						       *
************************************************************************************************/

#include "SUVATCalculator.h"

SUVATCalculator::SUVATCalculator(Vector3 _u, Vector3 _a, float _t) {
	m_VelocityU = _u;
	m_Acc       = _a;
	m_time      = _t;
	m_VelocityV = m_VelocityU + (m_Acc * m_time);
}

Vector3 SUVATCalculator::CalculateDisplacement(Vector3 _initVelocity, Vector3 _acc, float _t) {
	return ((_initVelocity * _t) + (_acc * _t *_t)*0.5f);
}

Vector3 SUVATCalculator::CalculateDisplacement(Vector3 _initVelocity, Vector3 _finalVelocity, float _t) {
	return ( (_initVelocity + _finalVelocity) * _t * 0.5f );
}

Vector3 SUVATCalculator::CalculateAcceleration(Vector3 _initVelocity, Vector3 _finalVelocity, float _t) {
	return (- (_initVelocity + _finalVelocity) / _t );
}
