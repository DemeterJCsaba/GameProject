#include "MainMenuState.h"

// Functions
void startGame() {
	StateManager::getInstance().addState(new SinglePlayerState());
}

void exitGame() {
	Window::getInstance().Close();
}


// Main menu state
MainMenuState::MainMenuState()
{
	init();

	// 2D objects
	m_LayerGUI->addModel("StartButton", new Button(vec2(-0.85f, 0.2f), vec2(0.35f, 0.15f), new Texture2D("Resources\\Images\\StartGameButton.png"), &startGame));
	m_LayerGUI->addModel("ExitButton", new Button(vec2(-0.85f, -0.35f), vec2(0.35f, 0.15f), new Texture2D("Resources\\Images\\ExitGameButton.png"), &exitGame));
	m_LayerGUI->addModel("BackGround", 
			new GUIImage(vec2(-1.0f, -1.0f),
			vec2(2.0f, 2.0f), 
			new Texture2D("Resources\\Images\\MainMenu_BG.png")));

	m_GUIManager.addButton((Button*)m_LayerGUI->getModel("StartButton"));
	m_GUIManager.addButton((Button*)m_LayerGUI->getModel("ExitButton"));

	// 3D objects
	//Entity* player = new Entity("Resources\\Entitys\\test.obj");
	//player->getRawModel()->setPosition(vec3(2.0f, -0.5f, -2.0f));
	//m_Layer3D->addModel("Player", player->getRawModel());
}

void MainMenuState::init() {
	// GUI Layer
	ShaderProgram* shader2d = new ShaderProgram("gui");
	shader2d->enable();
	GLint textures[32];
	for (int i = 0; i < 32; ++i) textures[i] = i;
	shader2d->setUniformiv("textures", textures, 32);
	shader2d->disable();
	m_LayerGUI = new LayerGUI(shader2d);

	// 3D Layer
	ShaderProgram* shader3d = new ShaderProgram("menu3D");
	shader3d->enable();
	shader3d->setUniformMat4("pr_matrix", mat4::perspective(70, Window::getInstance().getWidth()*1.0f / Window::getInstance().getHeight(), 0.1f, 1000));
	shader3d->disable();
	m_Layer3D = new Layer3DDynamic(shader3d);
}

MainMenuState::~MainMenuState() {
	
}

void MainMenuState::update() {
	//m_Layer3D->getModel("Player")->addRotation(vec3(0.0f, 0.1f, 0.0f));

	m_GUIManager.execute();
}

void MainMenuState::render() {
	m_LayerGUI->render();
	m_Layer3D->render();
}

void MainMenuState::resume() {
}

void MainMenuState::pause() {

}

