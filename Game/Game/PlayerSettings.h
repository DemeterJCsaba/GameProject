#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include <string>

#include "Maths.h"

using namespace std;

class PlayerSettings {
private:
	string m_Name;
	vec3 m_Color;
	vec3 m_Size;
public:
	PlayerSettings(string name, vec3 color, vec3 size);

	const vec3& getColor() const { return m_Color; }
	const vec3& getSize() const { return m_Size; }
	const string& getName() const { return m_Name; }
};

#endif // !PLAYERSETTINGS_H
