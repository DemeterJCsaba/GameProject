#include "LayerSky.h"

LayerSky::LayerSky():
	m_Renderer(RenderEngine3DTextured(true, 16))
{
	m_Changed = false;
}

LayerSky::~LayerSky() {
	
}

void LayerSky::addEntity(string name, RawModel3DTextured* model) {
	removeModel(name);
	m_Entities.push_back(make_pair(name, model));
	m_Changed = true;
}

RawModel3DTextured* LayerSky::getModel(string name) {
	for (pair<string, RawModel3DTextured*> &e : m_Entities) {
		if (e.first == name) {
			return e.second;
		}
	}
	return nullptr;
}

void LayerSky::removeModel(string name) {
	for (pair<string, RawModel3DTextured*> &e : m_Entities) {
		if (e.first == name) {
			m_Entities.remove(e);
		}
	}
	m_Changed = true;
}

void LayerSky::render() {
	if (m_Changed) {
		m_Renderer.begin();
		m_Renderer.addTexture(Texture2D::get("SkyGradient.png"));
		for(pair<string, RawModel3DTextured*> &e : m_Entities){
			m_Renderer.submit(*e.second);
		}
		m_Renderer.end();
		m_Changed = false;
	}

	if (m_ShaderPtr != nullptr) m_ShaderPtr->enable();
	m_Renderer.flush();
	if (m_ShaderPtr != nullptr) m_ShaderPtr->disable();
}