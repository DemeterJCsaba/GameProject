#pragma once

#include <map>

#include "RawModel3D.h"
#include "ShaderProgram.h"
#include "RenderEngine3D.h"

using namespace std;

class Layer3DDynamic {
private:
	RenderEngine3D m_Renderer;
	ShaderProgram* m_Shader;

	map<string, RawModel3D*> m_Models;
public:
	Layer3DDynamic(ShaderProgram* shader);

	void addModel(string name, RawModel3D* model);
	RawModel3D* getModel(string name);
	void removeModel(string name);

	void render();
};