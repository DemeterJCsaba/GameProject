#pragma once

#include <list>

#include "Layer.h"
#include "ShaderProgram.h"
#include "RenderEngine3D.h"
#include "Texture2D.h"

using namespace std;

class Layer3DStatic : public Layer{
private:
	RenderEngine3D m_Renderer;

	bool m_Changed;
	list<pair<string, RawModel3D*>> m_Entities;
public:
	Layer3DStatic();
	~Layer3DStatic();

	void addEntity(string name, RawModel3D* model);
	RawModel3D* getModel(string name);
	void removeModel(string name);

	void render();
};