#include "Layer2D.h"

Layer2D::Layer2D():
	m_Renderer(RenderEngine2D(true))
{

}

Layer2D::~Layer2D() {
	delete m_ShaderPtr.get();
}

void Layer2D::setShader(ShaderProgram* shader) {
	m_ShaderPtr = shared_ptr<ShaderProgram>(shader);
}

void Layer2D::addModel(string name, RawModel2D* model) {
	removeModel(name);
	m_Models.push_back(make_pair(name, model));
}

RawModel2D* Layer2D::getModel(string name) {
	for (pair<string, RawModel2D*> &e : m_Models) {
		if (e.first == name) {
			return e.second;
		}
	}
	return nullptr;
}

void Layer2D::removeModel(string name) {
	for (pair<string, RawModel2D*> &e : m_Models) {
		if (e.first == name) {
			m_Models.remove(e);
			break;
		}
	}
}

void Layer2D::udate() {
	
}

void Layer2D::render() {
	m_Renderer.begin();
	for (list<pair<string, RawModel2D*>>::iterator it = m_Models.begin(); it != m_Models.end(); ++it) {
		m_Renderer.submit(it->second);
	}
	m_Renderer.end();

	if (m_ShaderPtr != nullptr) m_ShaderPtr->enable();
	m_Renderer.flush();
	if (m_ShaderPtr != nullptr) m_ShaderPtr->disable();
}
