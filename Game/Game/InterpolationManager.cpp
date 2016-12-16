#include "InterpolationManeger.h"

#include <iostream>

InterpolationManager::InterpolationManager() {

}

InterpolationManager::~InterpolationManager() {
	for (auto interp : m_Interpolations) {
		delete interp;
	}
}

void InterpolationManager::addInterpolation(Interpolation* interpolation) {
	for (list<Interpolation*>::iterator i = m_Interpolations.begin(); i!= m_Interpolations.end() ; ++i) {
		if ((*i)->getModelPtr() == interpolation->getModelPtr()) {
			m_Interpolations.erase(i);
			break;
		}
	}
	m_Interpolations.push_back(interpolation);
}

void InterpolationManager::update() {
	for (list<Interpolation*>::iterator i = m_Interpolations.begin(); i != m_Interpolations.end(); ) {
		(*i)->update();
		if ((*i)->isDone()) {
			m_Interpolations.erase(i++);
		} else ++i;
	}
}