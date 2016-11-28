#include "MainMenuState.h"

MainMenuState::MainMenuState():
	m_ShaderGUI(ShaderProgram("gui")),
	m_Shader3D(ShaderProgram("menu3D"))
{
	// Temporal
	m_RenderEngine2D.begin();
	GUIImage BG(vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f), new Texture("Resources\\Images\\MainMenu_BG.png"));
	GUIImage StartButton(vec2(-0.85f, 0.2f), vec2(0.35f, 0.15f), new Texture("Resources\\Images\\StartGameButton.png"));
	GUIImage ExitButton(vec2(-0.85f,-0.35f),vec2(0.35f,0.15f),new Texture("Resources\\Images\\ExitGameButton.png"));
	m_RenderEngine2D.submit(BG);
	m_RenderEngine2D.submit(StartButton);
	m_RenderEngine2D.submit(ExitButton);
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

	double x = (Window::getInstance().getMousePosX()/ Window::getInstance().getWidth())*2.0 - 1.0;
	double y = (1.0 - Window::getInstance().getMousePosY()/ Window::getInstance().getHeight())*2.0 - 1.0;


	if (Window::getInstance().getMousePressed(GLFW_MOUSE_BUTTON_1) && x >= -0.85f && x <= (-0.85f + 0.35f) && y >= 0.2f && y <= (0.2f + 0.15f)) {
		StateManager::getInstance().addState(new SinglePlayerState());
	}
	if (Window::getInstance().getMousePressed(GLFW_MOUSE_BUTTON_1) && x >= -0.85f && x <= (-0.85f + 0.35f) && y >= -0.35f && y <= (-0.35f + 0.15f)) {
		Window::getInstance().Close();
	}

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