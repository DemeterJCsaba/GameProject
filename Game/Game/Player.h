#ifndef PLAYER_H
#define PLAYER_H

#include "LivingEntity.h"

class Player : public LivingEntity {
private:
	
public:
	Player(float health = 100.0f,vec3 position = vec3(),vec3 rotation = vec3(), vec3 scale = vec3(1.0f));

	void setColor(vec3 color);

	std::string toMyson();
};

#endif // !PLAYER_H