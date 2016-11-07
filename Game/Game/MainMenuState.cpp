#include "MainMenuState.h"

MainMenuState::MainMenuState():
	m_Shader(ShaderProgram("test"))
{
	m_RenderEngine2D.begin();
	GUI g;
	m_RenderEngine2D.submit(g);
	m_RenderEngine2D.end();
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::update() {

}

void MainMenuState::render() {
	m_Shader.enable();
	m_RenderEngine2D.flush();
	m_Shader.disable();
}