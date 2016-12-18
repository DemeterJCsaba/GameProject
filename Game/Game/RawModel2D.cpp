#include "RawModel2D.h"

RawModel2D::~RawModel2D() {
	for (RawModel2D* model : m_Models) {
		delete model;
	}
}

/*void RawModel2D::addModel(RawModel2D* model) {
	m_Models.push_back(model);
}*/

list<RawModel2D*>* RawModel2D::getList() {
	return &m_Models;
}