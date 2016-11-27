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
	vector<IState*> m_Stack;

	StateManager();
public:
	IState* getCurrentState();
	void addState(IState* state);
	void closeCurrentState();
};