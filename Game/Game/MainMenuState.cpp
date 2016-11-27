#include "MainMenuState.h"

MainMenuState::MainMenuState():
	m_ShaderGUI(ShaderProgram("test")),
	m_Shader3D(ShaderProgram("simple"))
{
	// Temporal
	m_RenderEngine2D.begin();
	GUI g(-0.5, -0.5);
	GUI g2(0,0,new Texture("Resources\\Images\\MainMenu_BG.png"));
	//m_RenderEngine2D.submit(g);
	m_RenderEngine2D.submit(g2);
	m_RenderEngine2D.end();

	m_ShaderGUI.enable();
	GLint textures[32];
	for (int i = 0; i < 32; ++i) {
		textures[i] = i;
	}
	m_ShaderGUI.setUniformiv("textures", textures, 32);
	m_ShaderGUI.disable();

	//Entity* player = new Entity("");
	//m_RenderEngine3DD.submit(player);
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::update() {
	Window::getInstance().setMouseVisibility(true);

	// Temporal
	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_E)) {
		StateManager::getInstance().addState(new SinglePlayerState());
	}
}

void MainMenuState::render() {
	m_ShaderGUI.enable();
	m_RenderEngine2D.flush();
	m_ShaderGUI.disable();

	m_Shader3D.enable();
	m_RenderEngine3DD.flush();
	m_Shader3D.disable();
}