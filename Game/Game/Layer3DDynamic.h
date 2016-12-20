#ifndef LAYER3DDYNAMIC_H
#define LAYER3DDYNAMIC_H

#include <map>
#include <memory>

#include "Movable.h"
#include "ShaderProgram.h"
#include "RenderEngine3D.h"

using namespace std;

class Layer3DDynamic {
private:
	RenderEngine3D m_Renderer;
	shared_ptr<ShaderProgram> m_ShaderPtr;

	map<string, Movable*> m_Models;
public:
	Layer3DDynamic();
	~Layer3DDynamic();

	void setShader(ShaderProgram* shader);
	ShaderProgram* getShader() const { return m_ShaderPtr.get(); }

	void addModel(string name, Movable* model);
	Movable* getModel(string name);
	void removeModel(string name);

	void udate();
	void render();
};

#endif // !LAYER3DDYNAMIC_H