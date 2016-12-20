#pragma once

#include <list>

#include "Layer.h"
#include "RenderEngine3DTextured.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

using namespace std;

class LayerSky : public Layer{
private:
	RenderEngine3DTextured m_Renderer;

	bool m_Changed;
	list<pair<string, RawModel3DTextured*>> m_Entities;
public:
	LayerSky();
	~LayerSky();

	void addEntity(string name,RawModel3DTextured* model);
	RawModel3DTextured* getModel(string name);
	void removeModel(string name);

	void render();
}; 