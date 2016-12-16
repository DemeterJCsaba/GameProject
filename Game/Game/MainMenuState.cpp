#include "MainMenuState.h"

#include "Interpolation.h"
#include "Delay.h"

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
	m_LayerGuiBGPtr = (shared_ptr<LayerGUI>) new LayerGUI(shader2d);

	// 3D Layer
	ShaderProgram* shader3d = new ShaderProgram("menu3D");
	shader3d->enable();
	shader3d->setUniformMat4("pr_matrix", mat4::perspective(50.0f, Window::GetInstance()->getWidth()*1.0f / Window::GetInstance()->getHeight(), 0.1f, 1000));
	shader3d->disable();
	m_Layer3DPtr = (shared_ptr<Layer3DDynamic>) new Layer3DDynamic(shader3d);
}

void MainMenuState::load() {
	// 2D objects
	m_LayerGuiBGPtr->addModel("BackGround",
		new GUIImage(vec2(-1.0f, -1.0f),
			vec2(2.0f, 2.0f),
			new Texture2D("Resources\\Images\\MainMenu_BG.png")));
	m_LayerGuiPtr->addModel("StartButton",
			new Button<MainMenuState>(vec2(-0.85f, 0.2f),
			vec2(0.35f, 0.15f),
			new Texture2D("Resources\\Images\\StartGameButton.png"),
			&MainMenuState::startGameButtonExecute,this));
	m_LayerGuiPtr->addModel("ExitButton",
			new Button<MainMenuState>(vec2(-0.85f, -0.35f),
			vec2(0.35f, 0.15f),
			new Texture2D("Resources\\Images\\ExitGameButton.png"),
			&MainMenuState::exitGame,this));
	m_LayerGuiPtr->addModel("SelectCharacter",
			new Button<MainMenuState>(vec2(0.3f, -0.7f),
			vec2(0.35f, 0.15f),
			new Texture2D("Resources\\Images\\SelectCharacterButton.png"),
			&MainMenuState::selectCaracter, this));
	m_LayerGuiPtr->addModel("Fade",
			new GUIImage(vec2(-1.0f, -1.0f),
			vec2(2.0f, 2.0f),
			new Texture2D("Resources\\Images\\Fade.png")));

	m_GUIManager.addButton((Button<MainMenuState>*)m_LayerGuiPtr->getModel("StartButton"));
	m_GUIManager.addButton((Button<MainMenuState>*)m_LayerGuiPtr->getModel("ExitButton"));
	m_GUIManager.addButton((Button<MainMenuState>*)m_LayerGuiPtr->getModel("SelectCharacter"));

	// 3D objects
	m_Layer3DPtr->addModel("Player", RawModel3D::loadFromOBJ("Resources\\Entitys\\kocka.obj"));
	m_Layer3DPtr->getModel("Player")->setPosition(vec3(3.0f, -0.5f, -7.0f));
}

MainMenuState::~MainMenuState() {
	
}

void MainMenuState::update() {
	m_GUIManager.execute();

	/*if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_Q)) {
		m_InterpolationManager.addInterpolation(new Interpolation2D(m_LayerGuiPtr->getModel("ExitButton"), 40, vec2(-2.0f, -0.35f)));
	}
	if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_W)) {
		m_InterpolationManager.addInterpolation(new Interpolation2D(m_LayerGuiPtr->getModel("ExitButton"), 40, vec2(-0.85f, -0.35f)));
	}*/
	if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_ESCAPE)) {
		backToMain();
	}

	m_TimerManager.update();
	m_Layer3DPtr->getModel("Player")->addRotation(vec3(0.0f, 0.1f, 0.0f));
}

void MainMenuState::render() {
	m_LayerGuiBGPtr->render();
	m_Layer3DPtr->render();
	m_LayerGuiPtr->render();
}

void MainMenuState::resume() {
	cout << "Main menu resume." << endl;

	m_LayerGuiPtr->getModel("StartButton")->setPosition(vec2(-2.0f, 0.2f));
	m_LayerGuiPtr->getModel("ExitButton")->setPosition(vec2(-2.0f, -0.35f));
	m_LayerGuiPtr->getModel("SelectCharacter")->setPosition(vec2(1.5f, -0.7f));
	mainButtonsIn();

	m_TimerManager.addTimer(new Interpolation<MainMenuState, float>(this, &MainMenuState::fade, 1.0f, 0.0f, 40));
}

void MainMenuState::pause() {
	cout << "Main menu pause." << endl;
}

// Button functions
void MainMenuState::backToMain() {
	mainButtonsIn();
	RawModel3D* player = m_Layer3DPtr->getModel("Player");
	m_TimerManager.addTimer(new Interpolation<RawModel3D, vec3>(
		player,
		&RawModel3D::setPosition,
		player->getPosition(),
		vec3(3.0f, -0.5f, -7.0f),
		40));
}

void MainMenuState::mainButtonsIn() {
	Button<MainMenuState>* startButton = (Button<MainMenuState>*)m_LayerGuiPtr->getModel("StartButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(
		startButton,
		&Button<MainMenuState>::setPosition,
		startButton->getPosition(),
		vec2(-0.85f, 0.2f),
		40));

	Button<MainMenuState>* exitButton = (Button<MainMenuState>*)m_LayerGuiPtr->getModel("ExitButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(
		exitButton,
		&Button<MainMenuState>::setPosition,
		exitButton->getPosition(),
		vec2(-0.85f, -0.35f),
		40));

	Button<MainMenuState>* selectCharacterButton = (Button<MainMenuState>*)m_LayerGuiPtr->getModel("SelectCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(
		selectCharacterButton,
		&Button<MainMenuState>::setPosition,
		selectCharacterButton->getPosition(),
		vec2(0.3f, -0.7f),
		40));
}

void MainMenuState::mainButtonsOut() {
	Button<MainMenuState>* startButton = (Button<MainMenuState>*)m_LayerGuiPtr->getModel("StartButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(
		startButton,
		&Button<MainMenuState>::setPosition,
		startButton->getPosition(),
		vec2(-2.0f, 0.2f),
		40));

	Button<MainMenuState>* exitButton = (Button<MainMenuState>*)m_LayerGuiPtr->getModel("ExitButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(
		exitButton,
		&Button<MainMenuState>::setPosition,
		exitButton->getPosition(),
		vec2(-2.0f, -0.35f),
		40));

	Button<MainMenuState>* selectCharacterButton = (Button<MainMenuState>*)m_LayerGuiPtr->getModel("SelectCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(
		selectCharacterButton,
		&Button<MainMenuState>::setPosition,
		selectCharacterButton->getPosition(),
		vec2(1.5f, -0.7f),
		40));
}

void MainMenuState::startGameButtonExecute() {
	m_TimerManager.addTimer(new Interpolation<MainMenuState, float>(this, &MainMenuState::fade, 0.0f, 1.0f, 40));
	m_TimerManager.addTimer(new Delay<MainMenuState>(this,&MainMenuState::startGame,40));
}

void MainMenuState::startGame() {
	StateManager::getInstance().addState(new SinglePlayerState());
}

void MainMenuState::exitGame() {
	Window::GetInstance()->close();
}

void MainMenuState::selectCaracter() {
	mainButtonsOut();
	RawModel3D* player = m_Layer3DPtr->getModel("Player");
	m_TimerManager.addTimer(new Interpolation<RawModel3D, vec3>(
		player,
		&RawModel3D::setPosition,
		player->getPosition(),
		vec3(0.0f, -0.5f, -5.5f),
		40));
}

void MainMenuState::fade(float value) {
	ShaderProgram* shader = m_LayerGuiPtr->getShader();
	shader->enable();
	shader->setUniform1f("fade", 1.0f-value);
	shader->disable();
}

