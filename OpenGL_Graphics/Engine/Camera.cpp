#include "Camera.h"

void Camera::UpdateCamera(float msec) {
	m_Pitch -= (Window::GetMouse()->GetRelativePosition().y);
	m_Yaw   -= (Window::GetMouse()->GetRelativePosition().x);

	m_Pitch = min(m_Pitch, 90.0f);
	m_Pitch = max(m_Pitch, -90.0f);

	if (m_Yaw < 0) {
		m_Yaw += 360.0f;
	}
	if (m_Yaw > 360.0f) {
		m_Yaw -= 360.0f;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		m_Position -= Matrix4::Rotation(m_Yaw, Vector3(0.0f, 1.0f, 0.0f)) * Vector3(0.0f, 0.0f, -1.0f) * msec;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		m_Position += Matrix4::Rotation(m_Yaw, Vector3(0.0f, 1.0f, 0.0f)) * Vector3(0.0f, 0.0f, -1.0f) * msec;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		m_Position += Matrix4::Rotation(m_Yaw, Vector3(0.0f, 1.0f, 0.0f)) * Vector3(-1.0f, 0.0f, 0.0f) * msec;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		m_Position -= Matrix4::Rotation(m_Yaw, Vector3(0.0f, 1.0f, 0.0f)) * Vector3(-1.0f, 0.0f, 0.0f) * msec;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
		m_Position.y += msec;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
		m_Position.y -= msec;
	}
};

Matrix4 Camera::BuildViewMatrix() {
	return Matrix4::Rotation(-m_Pitch, Vector3(1, 0, 0)) * Matrix4::Rotation(-m_Yaw, Vector3(0, 1, 0)) * Matrix4::Translation(-m_Position);
};