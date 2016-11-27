#include "MainMenuState.h"

MainMenuState::MainMenuState():
	m_ShaderGUI(ShaderProgram("test")),
	m_Shader3D(ShaderProgram("menu3D"))
{
	// Temporal
	m_RenderEngine2D.begin();
	GUIImage BG(vec2(-0.5f,-0.5f),vec2(2.0f,2.0f),new Texture("Resources\\Images\\MainMenu_BG.png"));
	m_RenderEngine2D.submit(BG);
	m_RenderEngine2D.end();

	m_ShaderGUI.enable();
	GLint textures[32];
	for (int i = 0; i < 32; ++i) {
		textures[i] = i;
	}
	m_ShaderGUI.setUniformiv("textures", textures, 32);
	m_ShaderGUI.disable();

	m_Shader3D.enable();
	m_Shader3D.setUniformMat4("pr_matrix", mat4::perspective(70, 960.0f / 540.0f, 0.1f, 1000));
	m_Shader3D.disable();

	player = new Entity("Resources\\Entitys\\test.obj");
	
	m_RenderEngine3DDynamic.submit(player->getRawModel());
}

MainMenuState::~MainMenuState() {
	
}

void MainMenuState::update() {
	player->getRawModel()->setPosition(vec3(2.0f, -0.5f, -2.0f));
	player->getRawModel()->addRotation(vec3(0.0f,0.1f,0.0f));

	// Temporal
	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_E)) {
		StateManager::getInstance().addState(new SinglePlayerState());
	}
}

void MainMenuState::render() {
	// 2D
	m_ShaderGUI.enable();
	m_RenderEngine2D.flush();
	m_ShaderGUI.disable();

	// 3D
	m_Shader3D.enable();
	m_RenderEngine3DDynamic.flush();
	m_Shader3D.disable();
}