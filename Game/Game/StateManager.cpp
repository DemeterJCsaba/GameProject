#include "StateManager.h"

StateManager& StateManager::getInstance() {
	static StateManager s_Instance;
	return s_Instance;
}

StateManager::StateManager() {}

// Returns the current state 
IState* StateManager::getCurrentState() {
	if (m_Stack.size() > 0)
		return m_Stack[m_Stack.size() - 1];
	else
		return nullptr;
}

// Add a new state
void StateManager::addState(IState* state) {
	if (state != nullptr)
		m_Stack.push_back(state);
}

// Close the curret state
void StateManager::closeCurrentState() {
	if (m_Stack.size() > 0) {
		IState* tmp = m_Stack[m_Stack.size() - 1];
		m_Stack.pop_back();
		delete tmp;
	}
}