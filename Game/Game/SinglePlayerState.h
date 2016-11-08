#pragma once

#include "IState.h"
#include "StateManager.h"
#include "Window.h"

class SinglePlayerState : public IState {
private:

public:
	SinglePlayerState();
	~SinglePlayerState();
	void update();
	void render();
};