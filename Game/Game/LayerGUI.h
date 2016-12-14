#pragma once

#include <map>

#include "RawModel2D.h"
#include "ShaderProgram.h"
#include "RenderEngine2D.h"

using namespace std;

class LayerGUI {
private:
	RenderEngine2D m_Renderer;
	ShaderProgram* m_Shader;

	map<string, RawModel2D*> m_Models;
public:
	LayerGUI(ShaderProgram* shader);

	void addModel(string name,RawModel2D* model);
	RawModel2D* getModel(string name);
	void removeModel(string name);

	void render();
};