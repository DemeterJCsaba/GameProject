#ifndef SINGLEPLAYERSTATE_H
#define SINGLEPLAYERSTATE_H

#include "IState.h"

#include "LayerSky.h"
#include "Layer3DStatic.h"
#include "Layer3DDynamic.h"
#include "Layer2D.h"

#include "Environment.h"
#include "Camera.h"

class SinglePlayerState : public IState {
private:
	Layer2D m_LayerGui;
	Layer3DDynamic m_Layer3DDynamic;
	LayerSky m_LayerSky;

	int m_BlockCount;
	int m_BlockSize;
	float m_SpriteSize;
	Layer3DStatic*** m_Layer3DStatic;
	int m_PosX;
	int m_PosZ;

	Environment m_Environment;
	//Camera* m_MainCamera;
	shared_ptr<Camera> m_MainCameraPtr;
public:
	SinglePlayerState();
	~SinglePlayerState();

	void update();
	void render();

	void resume();
	void pause();
private:
	void init();
	void load();

	void updateTerrain();
};

#endif // !SINGLEPLAYERSTATE_H