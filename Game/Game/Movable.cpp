#include "Movable.h"

void Movable::update() {
	m_Position += m_Motion;
	m_Motion = m_Motion*0.9f;
	m_Rotation += m_Rotate;
	m_Rotate = m_Rotate*0.9f;
}