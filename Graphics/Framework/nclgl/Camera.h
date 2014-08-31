/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   09.02.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Camera HEAD   	@details Advanced Programming 	 *
*																						 *
*****************************************************************************************/

#pragma once

#include "Window.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "GameTimer.h"

class Camera{
public:
	Camera(void){
		yaw = 0.0f;
		pitch = 0.0f;
	};

	Camera(float pitch, float yaw, Vector3 position){
		this->pitch = pitch;
		this->yaw = yaw;
		this->position = position;
	}

	~Camera(void){};

	void UpdateCamera(float msec = 10.0f);

	Matrix4 BuildViewMatrix();

	Vector3 GetPosition() const { return position; }
	void    SetPosition(Vector3 val) { position = val; }

	float GetYaw() const { return yaw; }
	void SetYaw(float y) { yaw = y; }

	float GetPitch() const { return pitch; }
	void SetPitch(float p) { pitch = p; }

	float GetDeltaT();

protected:
	float yaw;
	float pitch;
	float speed;
	Vector3 position;
	GameTimer time;
};