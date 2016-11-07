#include "MainMenuState.h"

MainMenuState::MainMenuState():
	m_Shader(ShaderProgram("test"))
{
	// Temporal
	m_RenderEngine2D.begin();
	GUI g(-0.5, -0.5);
	GUI g2(0,0,new Texture("Resources\\Images\\kep2.jpg"));
	//m_RenderEngine2D.submit(g);
	m_RenderEngine2D.submit(g2);
	m_RenderEngine2D.end();

	m_Shader.enable();
	GLint textures[32];
	for (int i = 0; i < 32; ++i) {
		textures[i] = i;
	}
	m_Shader.setUniformiv("textures", textures, 32);
	m_Shader.disable();
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