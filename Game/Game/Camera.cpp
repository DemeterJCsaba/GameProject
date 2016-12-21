#include "Camera.h"

#include <iostream>

const float Camera::Default_Speed = 0.03f;
Camera* Camera::Current = nullptr;

Camera::Camera(vec3 position, vec3 rotation, float distance, float speed):
	m_Distance(distance),
	m_Speed(speed),
	m_Position(position),
	m_Rotation(rotation)
{

}

void Camera::relaseEntity() {
	if (m_Entity != nullptr) {
		m_Position = m_Entity->getPosition();
		m_Rotation = m_Entity->getRotation();
		m_Entity = nullptr;
	}
}

void Camera::update() {
	if (m_Entity == nullptr) {
		float speed = m_Speed;
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_LEFT_SHIFT)) {
			speed = 20.0f;
		}
		m_Rotation.x += (float)Window::GetInstance()->getMouseOffsetY();
		m_Rotation.x = m_Rotation.x < -90.0f ? -90.0f : m_Rotation.x;
		m_Rotation.x = m_Rotation.x > 90.0f ? 90.0f : m_Rotation.x;
		m_Rotation.y += (float)Window::GetInstance()->getMouseOffsetX();
		m_Rotation.y += m_Rotation.y < 0.0f ? 360.0f : 0.0f;
		m_Rotation.y -= m_Rotation.y >= 360.0f ? 360.0f : 0.0f;

		float dx = speed*cos(toRadian(m_Rotation.x))*cos(toRadian(m_Rotation.y));
		float dy = speed*cos(toRadian(m_Rotation.x))*sin(toRadian(m_Rotation.y));
		float dz = speed*sin(toRadian(m_Rotation.x));
		float d2x = speed*cos(toRadian(m_Rotation.y));
		float d2y = speed*sin(toRadian(m_Rotation.y));
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_W)) {
			m_Position.x += dy;
			m_Position.y -= dz;
			m_Position.z -= dx;
		}
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_S)) {
			m_Position.x -= dy;
			m_Position.y += dz;
			m_Position.z += dx;
		}
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_A)) {
			m_Position.x -= d2x;
			m_Position.z -= d2y;
		}
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_D)) {
			m_Position.x += d2x;
			m_Position.z += d2y;
		}
	}
	else {
		float speed = m_Speed;
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_LEFT_SHIFT)) {
			speed = 0.5f;
		}
		m_Rotation.x += (float)Window::GetInstance()->getMouseOffsetY();
		m_Rotation.x = m_Rotation.x < -90.0f ? -90.0f : m_Rotation.x;
		m_Rotation.x = m_Rotation.x > 90.0f ? 90.0f : m_Rotation.x;
		m_Rotation.y += (float)Window::GetInstance()->getMouseOffsetX();
		m_Rotation.y += m_Rotation.y < 0.0f ? 360.0f : 0.0f;
		m_Rotation.y -= m_Rotation.y >= 360.0f ? 360.0f : 0.0f;

		vec3 rot = m_Entity->getRotation();
		rot.y = -m_Rotation.y + 180.0f;
		m_Entity->setRotation(rot);


		float dx = speed*cos(toRadian(m_Rotation.y));
		float dy = speed*sin(toRadian(m_Rotation.y));
		vec3 mot;
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_W)) {
			mot.x += dy;
			mot.z -= dx;
		}
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_S)) {
			mot.x -= dy;
			mot.z += dx;
		}
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_A)) {
			mot.x -= dx;
			mot.z -= dy;
		}
		if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_D)) {
			mot.x += dx;
			mot.z += dy;
		}
		mot.y = -0.5f;
		m_Entity->addMotion(mot);

		m_Position = m_Entity->getPosition();
		float height = Terrain::getHeight(12345, m_Position.x, m_Position.z, 5.0f);
		if (m_Position.y < height+5) {
			m_Entity->setPosition(vec3(m_Position.x, height + 5,m_Position.z));
		}
		m_Position.x += -m_Distance*cos(toRadian(m_Rotation.x))*sin(toRadian(m_Rotation.y));
		m_Position.y += m_Distance*sin(toRadian(m_Rotation.x));
		m_Position.z += m_Distance*cos(toRadian(m_Rotation.x))*cos(toRadian(m_Rotation.y));
	}
}

mat4 Camera::getMatrix() {
	return mat4::rotation(m_Rotation.x, 1, 0, 0)*
		   mat4::rotation(m_Rotation.y, 0, 1, 0)*
		   mat4::rotation(m_Rotation.z, 0, 0, 1)*
		   mat4::translation(-m_Position.x, -m_Position.y, -m_Position.z);
}

mat4 Camera::getRotationMatrix() {
	return mat4::rotation(m_Rotation.x, 1, 0, 0)*mat4::rotation(m_Rotation.y, 0, 1, 0)*mat4::rotation(m_Rotation.z, 0, 0, 1);
}

vec3 Camera::getPosition() {
	return m_Position;
}