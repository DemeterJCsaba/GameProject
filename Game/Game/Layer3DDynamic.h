#ifndef LAYER3DDYNAMIC_H
#define LAYER3DDYNAMIC_H

#include <map>

#include "Layer.h"
#include "Movable.h"
#include "ShaderProgram.h"
#include "RenderEngine3D.h"

using namespace std;

class Layer3DDynamic : public Layer {
private:
	RenderEngine3D m_Renderer;

	map<string, Movable*> m_Models;
public:
	Layer3DDynamic();
	~Layer3DDynamic();

	void addModel(string name, Movable* model);
	Movable* getModel(string name);
	void removeModel(string name);

	void udate();
	void render();
};

#endif // !LAYER3DDYNAMIC_H