#include "LayerGUI.h"

LayerGUI::LayerGUI(ShaderProgram* shader):
	m_Shader(shader),
	m_Renderer(RenderEngine2D(true))
{

}

void LayerGUI::addModel(string name, RawModel2D* model) {
	removeModel(name);
	m_Models[name] = model;
}

RawModel2D* LayerGUI::getModel(string name) {
	if (m_Models.find(name) != m_Models.end()) {
		return m_Models[name];
	}
	return nullptr;
}

void LayerGUI::removeModel(string name) {
	if (m_Models.find(name)!=m_Models.end()) {
		m_Models.erase(name);
	}
}

void LayerGUI::render() {
	m_Renderer.begin();
	for (map<string, RawModel2D*>::iterator it = m_Models.begin(); it != m_Models.end(); ++it) {
		m_Renderer.submit(it->second);
	}
	m_Renderer.end();

	m_Shader->enable();
	m_Renderer.flush();
	m_Shader->disable();
}