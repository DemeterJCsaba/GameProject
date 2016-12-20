#include "Player.h"

Player::Player(float health,vec3 position, vec3 rotation, vec3 scale):
	LivingEntity(health,position, rotation, scale)
{
	loadFromOBJ("Wolf.obj");
}

void Player::setColor(vec3 color) {
	m_Colors[0] = color;
}