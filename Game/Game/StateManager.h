#pragma once

#include <vector>

#include "IState.h"

using namespace std;

class StateManager {
private:
	static StateManager s_Instance;
public:
	static StateManager& getInstance();

private:
	StateManager();
	vector<IState*> m_Stack;
public:
	IState* getCurrentState();
	void pushState(IState* state);
	void popState();
};