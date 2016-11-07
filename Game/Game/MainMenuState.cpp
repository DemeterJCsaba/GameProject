#include "MainMenuState.h"

MainMenuState::MainMenuState() {
	m_RenderEngine2D.begin();
	GUI g;
	m_RenderEngine2D.submit(g);
	m_RenderEngine2D.end();
}

void MainMenuState::update() {

}

void MainMenuState::render() {
	m_RenderEngine2D.flush();
}