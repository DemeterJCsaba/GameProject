#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>

#include "IState.h"
#include "EventListener.h"

using namespace std;

class StateManager : public EventListener {
private:
	static StateManager s_Instance;
public:
	static StateManager& getInstance();

private:
	vector<IState*> m_Stack;
	int m_Close;

	StateManager();
	~StateManager();
public:
	IState* getCurrentState();

	void addState(IState* state);
	void update();
	void closeCurrentState(int count = 1); 
	void closeAll();
private:
};

#endif // !STATEMANAGER_H