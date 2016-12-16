#include "MainMenuState.h"

#include "Interpolation2D.h"

// Main menu functions
void startGame() {
	StateManager::getInstance().addState(new SinglePlayerState());
}

void exitGame() {
	Window::GetInstance()->close();
}


// Main menu state
MainMenuState::MainMenuState()
{
	init();
	load();
}

void MainMenuState::init() {
	// GUI Layer
	ShaderProgram* shader2d = new ShaderProgram("gui");
	shader2d->enable();
	GLint textures[32];
	for (int i = 0; i < 32; ++i) textures[i] = i;
	shader2d->setUniformiv("textures", textures, 32);
	shader2d->disable();
	m_LayerGuiPtr = (shared_ptr<LayerGUI>) new LayerGUI(shader2d);

	// 3D Layer
	ShaderProgram* shader3d = new ShaderProgram("menu3D");
	shader3d->enable();
	shader3d->setUniformMat4("pr_matrix", mat4::perspective(50.0f, Window::GetInstance()->getWidth()*1.0f / Window::GetInstance()->getHeight(), 0.1f, 1000));
	shader3d->disable();
	m_Layer3DPtr = (shared_ptr<Layer3DDynamic>) new Layer3DDynamic(shader3d);
}

void MainMenuState::load() {
	// 2D objects
	m_LayerGuiPtr->addModel("StartButton",
		new Button(vec2(-2.0f, 0.2f),
			vec2(0.35f, 0.15f),
			new Texture2D("Resources\\Images\\StartGameButton.png"),
			&startGame));
	m_LayerGuiPtr->addModel("ExitButton",
		new Button(vec2(-2.0f, -0.35f),
			vec2(0.35f, 0.15f),
			new Texture2D("Resources\\Images\\ExitGameButton.png"),
			&exitGame));
	m_LayerGuiPtr->addModel("BackGround",
		new GUIImage(vec2(-1.0f, -1.0f),
			vec2(2.0f, 2.0f),
			new Texture2D("Resources\\Images\\MainMenu_BG.png")));

	m_GUIManager.addButton((Button*)m_LayerGuiPtr->getModel("StartButton"));
	m_GUIManager.addButton((Button*)m_LayerGuiPtr->getModel("ExitButton"));

	// 3D objects
	m_Layer3DPtr->addModel("Player", RawModel3D::loadFromOBJ("Resources\\Entitys\\kocka.obj"));
	m_Layer3DPtr->getModel("Player")->setPosition(vec3(3.0f, -0.5f, -7.0f));
}

MainMenuState::~MainMenuState() {
	
}

void MainMenuState::update() {
	m_GUIManager.execute();

	if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_Q)) {
		m_InterpolationManager.addInterpolation(new Interpolation2D(m_LayerGuiPtr->getModel("ExitButton"), 40, vec2(-2.0f, -0.35f)));
	}
	if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_W)) {
		m_InterpolationManager.addInterpolation(new Interpolation2D(m_LayerGuiPtr->getModel("ExitButton"), 40, vec2(-0.85f, -0.35f)));
	}

	m_InterpolationManager.update();
	m_Layer3DPtr->getModel("Player")->addRotation(vec3(0.0f, 0.1f, 0.0f));
}

void MainMenuState::render() {
	m_LayerGuiPtr->render();
	m_Layer3DPtr->render();
}

void MainMenuState::resume() {
	cout << "Main menu resume." << endl;
	m_InterpolationManager.addInterpolation(new Interpolation2D(m_LayerGuiPtr->getModel("ExitButton"), 40, vec2(-0.85f, -0.35f)));
	m_InterpolationManager.addInterpolation(new Interpolation2D(m_LayerGuiPtr->getModel("StartButton"), 40, vec2(-0.85f, 0.2f)));
}

void MainMenuState::pause() {
	cout << "Main menu pause." << endl;
}

