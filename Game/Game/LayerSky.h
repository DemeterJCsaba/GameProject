#pragma once

#include <list>

#include "RenderEngine3DTextured.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

using namespace std;

class LayerSky {
private:
	RenderEngine3DTextured m_Renderer;
	ShaderProgram* m_Shader;

	bool m_Changed;
	list<pair<string, RawModel3DTextured*>> m_Entities;
public:
	LayerSky(ShaderProgram* shader);
	~LayerSky();

	void addEntity(string name,RawModel3DTextured* model);
	RawModel3DTextured* getModel(string name);
	void removeModel(string name);

	void render(mat4& viewMatrix, float time, vec3 sunDirection);
}; 