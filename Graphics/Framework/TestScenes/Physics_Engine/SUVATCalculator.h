/***********************************************************************************************
*	          .--.																		       *
*	::\`--._,'.::.`._.--'/::			@author Ana M. Mihut		@module Physics            *
*	::::. `  __::__ ' .:::::   			@alias  LT-Kerrigan			@date 28.09.2014	       *
*	::::::-:.`'..`'.:-::::::			@link								                   *
*	::::::::\ `--' /::::::::			@detail	Displacement V0 V1  Acc Time = SUVAT           *
*																						       *
************************************************************************************************/

#include "../../nclgl/Vector3.h"

class SUVATCalculator {
public:
	SUVATCalculator(void){};
	SUVATCalculator(Vector3 _initVelocity, Vector3 _acc, float _t);
	~SUVATCalculator(void){};

	Vector3 CalculateDisplacement(Vector3 _initVelocity, Vector3 _acc, float _t);
	Vector3 CalculateDisplacement(Vector3 _initVelocity, Vector3 _finalVelocity, float _t);
	Vector3 CalculateAcceleration(Vector3 _initVelocity, Vector3 _finalVelocity, float _t);

protected:
	Vector3 m_displacementS;
	Vector3 m_VelocityU;
	Vector3 m_VelocityV;
	Vector3 m_Acc;
	float   m_time;
};