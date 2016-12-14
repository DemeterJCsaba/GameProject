#ifndef STATEMANAGER_H
#define STATEMANAGER_H

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
	int m_Close;

	StateManager();
	// TODO: destructor
public:
	IState* getCurrentState();

	// This function 
	// <param>state<param>
	// This param is..
	void addState(IState* state);

	void Update();
	void closeCurrentState(int count = 1); 
	void closeAll();
private:
};

#endif // !STATEMANAGER_H