#include "Layer3DDynamic.h"

Layer3DDynamic::Layer3DDynamic()
{

}

Layer3DDynamic::~Layer3DDynamic()
{
	delete m_ShaderPtr.get();
}

void Layer3DDynamic::setShader(ShaderProgram* shader) {
	m_ShaderPtr = shared_ptr<ShaderProgram>(shader);
}

void Layer3DDynamic::addModel(string name, Movable* model) {
	removeModel(name);
	m_Models[name] = model;
}

Movable* Layer3DDynamic::getModel(string name) {
	if (m_Models.find(name) != m_Models.end()) {
		return m_Models[name];
	}
	return nullptr;
}

void Layer3DDynamic::removeModel(string name) {
	if (m_Models.find(name) != m_Models.end()) {
		m_Models.erase(name);
	}
}

void Layer3DDynamic::udate() {
	for (map<string, Movable*>::iterator it = m_Models.begin(); it != m_Models.end(); ++it) {
		it->second->update();
	}
}

void Layer3DDynamic::render() {
	m_Renderer.begin();
	for (map<string, Movable*>::iterator it = m_Models.begin(); it != m_Models.end(); ++it) {
		m_Renderer.submit(it->second);
	}
	m_Renderer.end();

	if (m_ShaderPtr != nullptr) m_ShaderPtr->enable();
	m_Renderer.flush();
	if (m_ShaderPtr != nullptr) m_ShaderPtr->disable();
}