#ifndef GUISTATE_H
#define GUISTATE_H

#include "Layer2D.h"
#include "Layer3DDynamic.h"

class GuiState {
private:
	Layer2D* m_LayerGuiPtr;
	Layer3DDynamic* m_Layer3DPtr;
public:
	GuiState(Layer2D* gui, Layer3DDynamic* dynamic3D) : m_LayerGuiPtr(gui),m_Layer3DPtr(dynamic3D){}

	virtual void start() = 0;
	virtual void end() = 0;
};

#endif // !GUISTATE_H