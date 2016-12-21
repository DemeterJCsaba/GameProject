#include "Player.h"

Player::Player(float health,vec3 position, vec3 rotation, vec3 scale):
	LivingEntity(health,position, rotation, scale)
{
	loadFromOBJ("Wolf.obj");
}

void Player::setColor(vec3 color) {
	m_Colors[0] = color;
}

std::string Player::toMyson()
{
	string json = string("health:") + to_string(m_Health) + string(";");
	json += string("position:") + to_string(m_Position.x) + string(":") + to_string(m_Position.y) + string(":") + to_string(m_Position.z) + string(";");
	json += string("rotation:") + to_string(m_Rotation.x) + string(":") + to_string(m_Rotation.y) + string(":") + to_string(m_Rotation.z) + string(";");
	json += string("scale:") + to_string(m_Scale.x) + string(":") + to_string(m_Scale.y) + string(":") + to_string(m_Scale.z) + string(";");
	json += string("motion:") + to_string(m_Motion.x) + string(":") + to_string(m_Motion.y) + string(":") + to_string(m_Motion.z) + string(";");
	json += string("color:") + to_string(m_Colors[0].x) + string(":") + to_string(m_Colors[0].y) + string(":") + to_string(m_Colors[0].z) + string(";");
	return json;
}
