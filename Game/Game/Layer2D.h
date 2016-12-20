#ifndef LAYER2D_H
#define LAYER2D_H

#include <list>
#include <memory>

#include "Layer.h"
#include "RawModel2D.h"
#include "ShaderProgram.h"
#include "RenderEngine2D.h"

using namespace std;

class Layer2D : public Layer{
private:
	RenderEngine2D m_Renderer;

	list<pair<string, RawModel2D*>> m_Models;
public:
	Layer2D();
	~Layer2D();

	void addModel(string name, RawModel2D* model);
	RawModel2D* getModel(string name);
	void removeModel(string name);

	void udate();
	void render();
};

#endif // !LAYER2D_H
