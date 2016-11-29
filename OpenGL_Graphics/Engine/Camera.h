#pragma once

#include "Window.h"
#include "Matrix4.h"
#include "Vector3.h"

class Camera {
public:
	Camera() {
		m_Yaw   = 0.0f;
		m_Pitch = 0.0f;
	}

	Camera(float pitch, float yaw, Vector3 position) {
		m_Pitch    = pitch;
		m_Yaw      = yaw;
		m_Position = position; 
	}

	~Camera() {};

	void UpdateCamera(float msec = 10.0f);

	Matrix4 BuildViewMatrix();

	Vector3 GetPosition() const { return m_Position; }
	void    SetPosition(Vector3 position) { m_Position = position; }

	float GetYaw() const	{ return m_Yaw; }
	void  SetYaw(float yaw) { m_Yaw = yaw; }

	float GetPitch() const		{ return m_Pitch; }
	void  SetPitch(float pitch) { m_Pitch = pitch; }

protected:
	float   m_Yaw;
	float   m_Pitch;
	Vector3 m_Position;
};