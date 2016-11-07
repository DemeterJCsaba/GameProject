#include "StateManager.h"

StateManager& StateManager::getInstance() {
	static StateManager s_Instance;
	return s_Instance;
}

StateManager::StateManager() {

}

IState* StateManager::getCurrentState() {
	if (m_Stack.size() > 0)
		return m_Stack[m_Stack.size() - 1];
	else
		return nullptr;
	// Todo: Exception
}

void StateManager::pushState(IState* state) {
	if (state != nullptr)
		m_Stack.push_back(state);
}

void StateManager::popState() {
	if (m_Stack.size() > 0) {
		IState* tmp = m_Stack[m_Stack.size() - 1];
		m_Stack.pop_back();
		delete tmp;
	}
}