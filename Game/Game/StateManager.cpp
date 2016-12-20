#include "StateManager.h"



StateManager& StateManager::getInstance() {
	static StateManager s_Instance;
	return s_Instance;
}



StateManager::StateManager() {
	m_Close = 0;
}

StateManager::~StateManager() {
	closeAll();
}

IState* StateManager::getCurrentState() {
	if (m_Stack.size() > 0)
		return m_Stack[m_Stack.size() - 1];
	else
		return nullptr;
}

void StateManager::addState(IState* state) {
	if (state != nullptr) {
		for (list<Event*>::iterator i = m_Events.begin(); i != m_Events.end(); ) {
			delete (*i++);
		}
		m_Events.clear();

		if (m_Stack.size() > 0) m_Stack[m_Stack.size() - 1]->pause();
		m_Stack.push_back(state);
		state->resume();
	}
}

void StateManager::update() {
	for (int i = 0; i < m_Close; ++i) {
		if (m_Stack.size() > 0) {
			IState* state = m_Stack[m_Stack.size() - 1];
			m_Stack.pop_back();
			state->pause();
			//delete state;
		}
	}
	if (m_Close!=0 && m_Stack.size() > 0) m_Stack[m_Stack.size() - 1]->resume();
	m_Close = 0;

	if (m_Stack.size() > 0) {
		for (Event* e : m_Events) {
			m_Stack[m_Stack.size() - 1]->addEvent(e);
		}
		m_Events.clear();
	}
}

void StateManager::closeCurrentState(int count) {
	m_Close = count;
}

void StateManager::closeAll() {
	m_Close = m_Stack.size();
}