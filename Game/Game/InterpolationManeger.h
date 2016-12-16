#ifndef INTERPOLATIONMANAGER_H
#define INTERPOLATIONMANAGER_H

#include <list>

#include "Interpolation.h"

using namespace std;

class InterpolationManager {
private:
	list<Interpolation*> m_Interpolations;
public:
	InterpolationManager();
	~InterpolationManager();

	void addInterpolation(Interpolation* interpolation);
	void update();
};

#endif // !INTERPOLATIONMANAGER_H