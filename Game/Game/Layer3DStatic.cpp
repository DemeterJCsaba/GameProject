#include "Layer3DStatic.h"

Layer3DStatic::Layer3DStatic(ShaderProgram* shader):
	m_Renderer(RenderEngine3D(false,135000)),
	m_Shader(shader)
{
	m_Changed = false;
}

Layer3DStatic::~Layer3DStatic() {

}

void Layer3DStatic::addEntity(string name, RawModel3D* model) {
	removeModel(name);
	m_Entities.push_back(make_pair(name, model));
	m_Changed = true;
}

RawModel3D* Layer3DStatic::getModel(string name) {
	for (pair<string, RawModel3D*> &e : m_Entities) {
		if (e.first == name) {
			return e.second;
		}
	}
	return nullptr;
}

void Layer3DStatic::removeModel(string name) {
	for (pair<string, RawModel3D*> &e : m_Entities) {
		if (e.first == name) {
			m_Entities.remove(e);
			break;
		}
	}
	m_Changed = true;
}


void Layer3DStatic::render(mat4& viewMatrix, float time, vec3 sunDirection) {
	if (m_Changed) {
		m_Renderer.begin();
		m_Renderer.addTexture(new Texture2D("Resources\\Images\\SkyGradient.png"));
		for (pair<string, RawModel3D*> &e : m_Entities) {
			m_Renderer.submit(e.second);
		}
		m_Renderer.end();
		m_Changed = false;
	}

	m_Shader->enable();

	m_Shader->setUniformMat4("vw_matrix", viewMatrix);
	m_Shader->setUniform3f("sunPosition", sunDirection);
	m_Shader->setUniform1f("time", time);
	
	m_Renderer.flush();

	m_Shader->disable();
}