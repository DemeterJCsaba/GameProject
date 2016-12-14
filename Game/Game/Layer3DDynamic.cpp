#include "Layer3DDynamic.h"

Layer3DDynamic::Layer3DDynamic(ShaderProgram* shader):
	m_Shader(shader)
{

}

void Layer3DDynamic::addModel(string name, RawModel3D* model) {
	removeModel(name);
	m_Models[name] = model;
}

RawModel3D* Layer3DDynamic::getModel(string name) {
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

void Layer3DDynamic::render() {
	m_Renderer.begin();
	for (map<string, RawModel3D*>::iterator it = m_Models.begin(); it != m_Models.end(); ++it) {
		m_Renderer.submit(it->second);
	}
	m_Renderer.end();

	m_Shader->enable();
	m_Renderer.flush();
	m_Shader->disable();
}