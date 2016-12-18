#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include "Movable.h"

class LivingEntity : public Movable {
protected:
	float m_Health;
public:
	LivingEntity(float health = 100.0f, vec3 position = vec3(), vec3 rotation = vec3(), vec3 scale = vec3(1.0f)) :Movable(position, rotation, scale),m_Health(health) {}

	void addHealth(float health) { m_Health += health; }
	void setHealth(float health) { m_Health = health; }
	float getHealth() const { return m_Health; }
};

#endif // !LIVINGENTITY_H
