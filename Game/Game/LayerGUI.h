#pragma once

#include <list>

#include "RawModel2D.h"
#include "ShaderProgram.h"
#include "RenderEngine2D.h"

using namespace std;

class LayerGUI {
private:
	RenderEngine2D m_Renderer;
	ShaderProgram* m_Shader;

	list<pair<string, RawModel2D*>> m_Models;
public:
	LayerGUI(ShaderProgram* shader);

	ShaderProgram* getShader() const { return m_Shader; }

	void addModel(string name,RawModel2D* model);
	RawModel2D* getModel(string name);
	void removeModel(string name);

	void render();
};