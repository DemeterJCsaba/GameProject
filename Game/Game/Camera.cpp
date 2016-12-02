#include "Camera.h"

Camera* Camera::current = nullptr;

Camera::Camera(Terrain* terrain, float distance):
	m_Terrain(terrain),
	m_Distance(distance)
{
	m_Position = vec3(0, 0, 0);
	m_Rotation = vec3(0, 0, 0);

	m_Speed = 0.3f;
}

void Camera::update() {
	if (m_Entity == nullptr) {
		float speed = m_Speed;
		if (Window::getInstance().getKeyboarPressed(GLFW_KEY_LEFT_SHIFT)) {
			speed = 20.0f;
		}
		m_Rotation.x += (float)Window::getInstance().getMouseOffsetY();
		m_Rotation.x = m_Rotation.x < -90.0f ? -90.0f : m_Rotation.x;
		m_Rotation.x = m_Rotation.x > 90.0f ? 90.0f : m_Rotation.x;
		m_Rotation.y += (float)Window::getInstance().getMouseOffsetX();
		m_Rotation.y += m_Rotation.y < 0.0f ? 360.0f : 0.0f;
		m_Rotation.y -= m_Rotation.y >= 360.0f ? 360.0f : 0.0f;

		float dx = speed*cos(toRadian(m_Rotation.x))*cos(toRadian(m_Rotation.y));
		float dy = speed*cos(toRadian(m_Rotation.x))*sin(toRadian(m_Rotation.y));
		float dz = speed*sin(toRadian(m_Rotation.x));
		float d2x = speed*cos(toRadian(m_Rotation.y));
		float d2y = speed*sin(toRadian(m_Rotation.y));
		if (Window::getInstance().getKeyboarPressed(GLFW_KEY_W)) {
			m_Position.x += dy;
			m_Position.y -= dz;
			m_Position.z -= dx;
		}
		if (Window::getInstance().getKeyboarPressed(GLFW_KEY_S)) {
			m_Position.x -= dy;
			m_Position.y += dz;
			m_Position.z += dx;
		}
		if (Window::getInstance().getKeyboarPressed(GLFW_KEY_A)) {
			m_Position.x -= d2x;
			m_Position.z -= d2y;
		}
		if (Window::getInstance().getKeyboarPressed(GLFW_KEY_D)) {
			m_Position.x += d2x;
			m_Position.z += d2y;
		}
	}

	if (m_Terrain != nullptr) {
		float height = m_Terrain->getHeight(m_Position.x / m_Terrain->getSize(), m_Position.z / m_Terrain->getSize());
		if (m_Position.y < height+1) {
			m_Position.y = height+1;
		}
	}
}

mat4 Camera::getMatrix() {
	//if (m_Entity != nullptr) {
		//return m_Entity->getMatrix();
	//}
	//else {
		return 
			   mat4::rotation(m_Rotation.x, 1, 0, 0) *
			   mat4::rotation(m_Rotation.y, 0, 1, 0) * mat4::translation(-m_Position.x, -m_Position.y, -m_Position.z) /*
			   mat4::rotation(m_Rotation.z, 0, 0, 1)*/;
	//}
}

mat4 Camera::getRotationMatrix() {
	return mat4::rotation(m_Rotation.x, 1, 0, 0) *
		   mat4::rotation(m_Rotation.y, 0, 1, 0);
}