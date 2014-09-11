/*****************************************************************************************
* 	         .--.              															 *
* ::\`--._,'.::.`._.--'/::     @author Ana M. Mihut		@course  Graphics				 *
* ::::.  ` __::__ '  .::::     @alias  LT-Kerrigan		@link    cs.ncl.ac.uk			 *
* ::::::-:.`'..`'.:-::::::     @date   09.02.2014       @origin  Newcastle 				 *
* ::::::::\ `--' /::::::::     @title  Camera CLASS   	@details Advanced Programming 	 *
*																						 *
*****************************************************************************************/

#include "Camera.h"

void Camera::UpdateCamera(float msec){

	pitch -= (Window::GetMouse()->GetRelativePosition().y);
	yaw -= (Window::GetMouse()->GetRelativePosition().x);

	pitch = min(pitch, 90.0f);
	pitch = max(pitch, -90.0f);

	if (yaw < 0){
		yaw += 360.0f;
	}

	if (yaw > 360.0f){
		yaw -= 360.0f;
	}

	speed = time.GetTimedMS();

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)){
		position += Matrix4::Rotation(yaw, Vector3(0.0f, 1.0f, 0.0f)) *
			Vector3(0.0f, 0.0f, -1.0f) * msec;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)){
		position -= Matrix4::Rotation(yaw, Vector3(0.0f, 1.0f, 0.0f)) *
			Vector3(0.0f, 0.0f, -1.0f) * msec;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)){
		position += Matrix4::Rotation(yaw, Vector3(0.0f, 1.0f, 0.0f)) *
			Vector3(-1.0f, 0.0f, 0.0f) * msec;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)){
		position -= Matrix4::Rotation(yaw, Vector3(0.0f, 1.0f, 0.0f)) *
			Vector3(-1.0f, 0.0f, 0.0f) * msec;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)){
		position.y += msec;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)){
		position.y -= msec;
	}
}

	Matrix4 Camera::BuildViewMatrix(){
		return Matrix4::Rotation(-pitch, Vector3(1,0,0)) *
			   Matrix4::Rotation(-yaw, Vector3(0,1,0)) *
			   Matrix4::Translation(-position);
	};

	float Camera::GetDeltaT(){
		GameTimer time;
		float currentTime = time.GetMS();
		float lastTime = time.GetTimedMS();
		float deltaTime = float(currentTime - lastTime);

		return deltaTime;
	}