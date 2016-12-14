#include "StateManager.h"

StateManager& StateManager::getInstance() {
	static StateManager s_Instance;
	return s_Instance;
}

StateManager::StateManager() {
	m_Close = 0;
}

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
	if (m_Stack.size() > 0) m_Stack[m_Stack.size() - 1]->pause();
	state->resume();
}

void StateManager::Update() {
	for (int i = 0; i < m_Close; ++i) {
		if (m_Stack.size() > 0) {
			IState* state = m_Stack[m_Stack.size() - 1];
			m_Stack.pop_back();
			state->pause();
			delete state;
		}
	}
	if (m_Close!=0 && m_Stack.size() > 0) m_Stack[m_Stack.size() - 1]->resume();
	m_Close = 0;
}

// Close the curret state
void StateManager::closeCurrentState(int count) {
	m_Close = count;
}

void StateManager::closeAll() {
	m_Close = m_Stack.size();
}