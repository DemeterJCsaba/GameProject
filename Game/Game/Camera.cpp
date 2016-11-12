#include "Camera.h"

Camera* Camera::current = nullptr;

Camera::Camera() {
	m_Position = vec3(0, 0, 0);
	m_Rotation = vec3(0, 0, 0);
}

mat4 Camera::getMatrix() {
	return mat4::translation(-m_Position.x, -m_Position.y, -m_Position.z) *
		mat4::rotation(m_Rotation.x, 1, 0, 0) *
		mat4::rotation(m_Rotation.y, 0, 1, 0) *
		mat4::rotation(m_Rotation.z, 0, 0, 1);
}

void Camera::setCurrentCamera() {
	current = this;
}

void Camera::tmp() {
	m_Rotation.y += 0.2;
}