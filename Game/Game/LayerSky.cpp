#include "LayerSky.h"

LayerSky::LayerSky(ShaderProgram* shader):
	m_Renderer(RenderEngine3DTextured(true, 16)),
	m_Shader(shader)
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

void LayerSky::render(mat4& viewMatrix,float time,vec3 sunDirection) {
	if (m_Changed) {
		m_Renderer.begin();
		m_Renderer.addTexture(new Texture2D("Resources\\Images\\SkyGradient.png"));
		for(pair<string, RawModel3DTextured*> &e : m_Entities){
			m_Renderer.submit(*e.second);
		}
		m_Renderer.end();
		m_Changed = false;
	}

	m_Shader->enable();

	m_Shader->setUniformMat4("vw_matrix", viewMatrix);
	m_Shader->setUniformMat4("rot_matrix", mat4::rotation(time, -1, 0, 0));
	m_Shader->setUniform3f("sunPosition", sunDirection);
	m_Shader->setUniform1f("time", time);

	m_Renderer.flush();

	m_Shader->disable();
}