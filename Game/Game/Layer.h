#ifndef LAYER_H
#define LAYER_H

#include <memory>

#include "ShaderProgram.h"

using namespace std;

class Layer {
protected:
	shared_ptr<ShaderProgram> m_ShaderPtr;
public:
	void setShader(ShaderProgram* shader) { m_ShaderPtr = shared_ptr<ShaderProgram>(shader); }
	ShaderProgram* getShader() const { return m_ShaderPtr.get(); }
};

#endif // !LAYER_H
