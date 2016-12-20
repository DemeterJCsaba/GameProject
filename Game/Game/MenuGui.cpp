#include "MenuGui.h"

#include <string>

#include "Texture2D.h"
#include "RawModel3D.h"
#include "Interpolation.h"
#include "Delay.h"
#include "StateManager.h"
#include "SinglePlayerState.h"
#include "Text.h"
#include "KeyboardButtonEvent.h"
#include "Slider.h"
#include "Player.h"
#include "SettingsManager.h"

MenuGui::MenuGui(Layer2D* layerGui, Layer3DDynamic* layer3D):
	m_LayerGuiPtr(layerGui),
	m_Layer3DPtr(layer3D)
{
	
}

void MenuGui::load() {
	m_LayerGuiPtr->addModel("Fade", new GUIImage(vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f), Texture2D::get("Fade.png")));
	m_LayerGuiPtr->addModel("Text", new Text("The Game - v0.0 (pre alpha)",vec2(-0.9f, -0.9f),0.35f));
	// State main
	m_LayerGuiPtr->addModel("StartButton", new Button<MenuGui>("Start Game", vec2(-0.85f, 0.2f), vec2(0.35f, 0.15f), &MenuGui::startGameButtonExecute, this));
	m_LayerGuiPtr->addModel("ExitButton", new Button<MenuGui>("Exit Game", vec2(-0.85f, -0.35f), vec2(0.35f, 0.15f), &MenuGui::exitGame, this));
	m_LayerGuiPtr->addModel("SelectCharacter", new Button<MenuGui>("Select Character", vec2(0.3f, -0.7f), vec2(0.35f, 0.15f), &MenuGui::selectCaracter, this));
	// State select character
	m_LayerGuiPtr->addModel("Back", new Button<MenuGui>("Back", vec2(0.45f, -0.55f), vec2(0.35f, 0.15f), &MenuGui::back, this));
	m_LayerGuiPtr->addModel("NewCharacter", new Button<MenuGui>("New Character", vec2(-0.85f, -0.35f), vec2(0.35f, 0.15f), &MenuGui::newCharater, this));
	m_LayerGuiPtr->addModel("NextCharacter", new Button<MenuGui>("Next", vec2(-0.85f, -0.2f), vec2(0.35f, 0.15f), &MenuGui::next, this));
	m_LayerGuiPtr->addModel("PreviuosCharacter", new Button<MenuGui>("Previous", vec2(-0.85f, -0.15f), vec2(0.35f, 0.15f), &MenuGui::previous, this));
	// State create character
	m_LayerGuiPtr->addModel("CreateCharacter", new Button<MenuGui>("Create Character", vec2(-0.85f, -0.75f), vec2(0.35f, 0.15f), &MenuGui::createCharacter, this));
	m_LayerGuiPtr->addModel("SizeSlider", new Slider(vec2(-0.85f, -0.5f), vec2(0.4f, 0.1f), 1.0f, 3.0f));
	m_LayerGuiPtr->addModel("ColorRSlider", new Slider(vec2(-0.85f, -0.35f), vec2(0.4f, 0.1f), 0.0f, 1.0f));
	m_LayerGuiPtr->addModel("ColorGSlider", new Slider(vec2(-0.85f, -0.2f), vec2(0.4f, 0.1f), 0.0f, 1.0f));
	m_LayerGuiPtr->addModel("ColorBSlider", new Slider(vec2(-0.85f,-0.05f), vec2(0.4f, 0.1f), 0.0f, 1.0f));
	// load players
	vector<PlayerSettings*>* players = SettingsManager::Instance->getPlayerSettings();
	for (PlayerSettings* player : *players) {
		
	}

	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("StartButton"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("ExitButton"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("SelectCharacter"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("Back"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("NextCharacter"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("PreviuosCharacter"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("NewCharacter"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("CreateCharacter"));

	m_GUIManager.addSlider((Slider*)m_LayerGuiPtr->getModel("SizeSlider"));
	m_GUIManager.addSlider((Slider*)m_LayerGuiPtr->getModel("ColorRSlider"));
	m_GUIManager.addSlider((Slider*)m_LayerGuiPtr->getModel("ColorGSlider"));
	m_GUIManager.addSlider((Slider*)m_LayerGuiPtr->getModel("ColorBSlider"));
}

void MenuGui::start() {
	m_LayerGuiPtr->getModel("StartButton")->setPosition(vec2(-2.0f, 0.2f));
	m_LayerGuiPtr->getModel("ExitButton")->setPosition(vec2(-2.0f, -0.35f));
	m_LayerGuiPtr->getModel("SelectCharacter")->setPosition(vec2(1.5f, -0.7f));
	m_LayerGuiPtr->getModel("Back")->setPosition(vec2(1.5f, -0.55f));
	m_LayerGuiPtr->getModel("NextCharacter")->setPosition(vec2(-2.0f, -0.35f));
	m_LayerGuiPtr->getModel("PreviuosCharacter")->setPosition(vec2(-2.0f, -0.15f));
	m_LayerGuiPtr->getModel("NewCharacter")->setPosition(vec2(-2.0f, -0.75f));
	m_LayerGuiPtr->getModel("CreateCharacter")->setPosition(vec2(-2.0f, -0.75f));
	m_LayerGuiPtr->getModel("SizeSlider")->setPosition(vec2(-2.0f, -0.5f));
	m_LayerGuiPtr->getModel("ColorRSlider")->setPosition(vec2(-2.0f, -0.35f));
	m_LayerGuiPtr->getModel("ColorGSlider")->setPosition(vec2(-2.0f, -0.2f));
	m_LayerGuiPtr->getModel("ColorBSlider")->setPosition(vec2(-2.0f, -0.05f));
	stateMainIn();

	m_TimerManager.addTimer(new Interpolation<MenuGui, float>(this, &MenuGui::fade, 1.0f, 0.0f, 40));
	state = 0;
}

void MenuGui::update() {
	m_GUIManager.update();

	Player* player = (Player*)m_Layer3DPtr->getModel("Player");
	if (player != nullptr && state == CREATE_CHARACTER) {
		Slider* slider = (Slider*)m_LayerGuiPtr->getModel("SizeSlider");
		player->setScale(vec3(slider->getValue()));
		player->setColor(vec3(
			((Slider*)m_LayerGuiPtr->getModel("ColorRSlider"))->getValue(),
			((Slider*)m_LayerGuiPtr->getModel("ColorGSlider"))->getValue(),
			((Slider*)m_LayerGuiPtr->getModel("ColorBSlider"))->getValue()
		));
	}

	m_TimerManager.update();
}

void MenuGui::handleEvent(Event* event) {
	if (event->getEvent() == Event::EVENTS::KEYBOARD_BUTTON) {
		KeyboardButtonEvent* keyboardEvent = (KeyboardButtonEvent*)event;
		if (keyboardEvent->getKeyCode() == GLFW_KEY_ESCAPE && keyboardEvent->getActionCode() == GLFW_PRESS) {
			back();
		}
	}
	else if (event->getEvent() == Event::EVENTS::MOUSE_BUTTON) {
		MouseButtonEvent* mouseEvent = (MouseButtonEvent*)event;
		m_GUIManager.execute(mouseEvent);
	}
}


//////// States main
void MenuGui::stateMainIn() {
	state = MAIN;

	RawModel3D* player = m_Layer3DPtr->getModel("Player");
	if(player !=nullptr)
		m_TimerManager.addTimer(new Interpolation<RawModel3D, vec3>(player, &RawModel3D::setPosition, player->getPosition(), vec3(3.0f, -0.5f, -7.0f), 40));

	RawModel2D* startButton = m_LayerGuiPtr->getModel("StartButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(startButton, &RawModel2D::setPosition, startButton->getPosition(), vec2(-0.85f, 0.2f), 40));

	RawModel2D* exitButton = m_LayerGuiPtr->getModel("ExitButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(exitButton, &RawModel2D::setPosition, exitButton->getPosition(), vec2(-0.85f, -0.35f), 40));

	RawModel2D* selectCharacterButton = m_LayerGuiPtr->getModel("SelectCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(selectCharacterButton, &RawModel2D::setPosition, selectCharacterButton->getPosition(), vec2(0.3f, -0.7f), 40));
}

void MenuGui::stateMainOut() {
	RawModel2D* startButton = m_LayerGuiPtr->getModel("StartButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(startButton, &RawModel2D::setPosition, startButton->getPosition(), vec2(-2.0f, 0.2f), 40));

	RawModel2D* exitButton = m_LayerGuiPtr->getModel("ExitButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(exitButton, &RawModel2D::setPosition, exitButton->getPosition(), vec2(-2.0f, -0.35f), 40));

	RawModel2D* selectCharacterButton = m_LayerGuiPtr->getModel("SelectCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(selectCharacterButton, &RawModel2D::setPosition, selectCharacterButton->getPosition(), vec2(1.5f, -0.7f), 40));
}

// Functions
void MenuGui::startGameButtonExecute() {
	m_TimerManager.addTimer(new Interpolation<MenuGui, float>(this, &MenuGui::fade, 0.0f, 1.0f, 40));
	m_TimerManager.addTimer(new Delay<MenuGui>(this, &MenuGui::startGame, 40));
}

void MenuGui::startGame() {
	StateManager::getInstance().addState(new SinglePlayerState());
}

void MenuGui::exitGame() {
	Window::GetInstance()->close();
}

void MenuGui::selectCaracter() {
	stateMainOut();
	stateSelectCharacterIn();
}

void MenuGui::fade(float value) {
	ShaderProgram* shader = m_LayerGuiPtr->getShader();
	shader->enable();
	shader->setUniform1f("fade", 1.0f - value);
	shader->disable();
}


//////// State select character
void MenuGui::stateSelectCharacterIn() {
	state = SELECT_CHARACTER;

	RawModel3D* player = m_Layer3DPtr->getModel("Player");
	if (player != nullptr)
		m_TimerManager.addTimer(new Interpolation<RawModel3D, vec3>(player, &RawModel3D::setPosition, player->getPosition(), vec3(0.0f, -0.5f, -5.5f), 40));

	RawModel2D* backButton = m_LayerGuiPtr->getModel("Back");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(backButton, &RawModel2D::setPosition, backButton->getPosition(), vec2(0.45f, -0.55f), 40));

	RawModel2D* newCharacterButton = m_LayerGuiPtr->getModel("NewCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(newCharacterButton, &RawModel2D::setPosition, newCharacterButton->getPosition(), vec2(-0.85f, -0.75f), 40));

	RawModel2D* nextCharacterButton = m_LayerGuiPtr->getModel("NextCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(nextCharacterButton, &RawModel2D::setPosition, nextCharacterButton->getPosition(), vec2(-0.85f, -0.35f), 40));

	RawModel2D* previousCharacterButton = m_LayerGuiPtr->getModel("PreviuosCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(previousCharacterButton, &RawModel2D::setPosition, previousCharacterButton->getPosition(), vec2(-0.85f, -0.15f), 40));
}

void MenuGui::stateSelectCharacterOut() {
	RawModel2D* backButton = m_LayerGuiPtr->getModel("Back");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(backButton, &RawModel2D::setPosition, backButton->getPosition(), vec2(1.5f, -0.55f), 40));

	RawModel2D* newCharacterButton = m_LayerGuiPtr->getModel("NewCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(newCharacterButton, &RawModel2D::setPosition, newCharacterButton->getPosition(), vec2(-2.0f, -0.75f), 40));

	RawModel2D* nextCharacterButton = m_LayerGuiPtr->getModel("NextCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(nextCharacterButton, &RawModel2D::setPosition, nextCharacterButton->getPosition(), vec2(-2.0f, -0.35f), 40));

	RawModel2D* previousCharacterButton = m_LayerGuiPtr->getModel("PreviuosCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(previousCharacterButton, &RawModel2D::setPosition, previousCharacterButton->getPosition(), vec2(-2.0f, -0.15f), 40));
}

// Functions
void MenuGui::back() {
	if (state == CREATE_CHARACTER) {
		stateCreateCharacterOut();
		stateSelectCharacterIn();

		Player* player = (Player*)m_Layer3DPtr->getModel("Player");
		if (player != nullptr) {
			PlayerSettings* ps = (*(SettingsManager::Instance->getPlayerSettings()))[SettingsManager::Instance->getSelectedPlayerIndex()-1];
			player->setColor(ps->getColor());
			player->setScale(ps->getSize());
		}
	}
	else if(state == SELECT_CHARACTER) {
		stateSelectCharacterOut();
		stateMainIn();
	}
}

void MenuGui::newCharater() {
	stateSelectCharacterOut();
	stateCreateCharacterIn();
	((Slider*)m_LayerGuiPtr->getModel("SizeSlider"))->setValue(1.0f);
	((Slider*)m_LayerGuiPtr->getModel("ColorRSlider"))->setValue(0.0f);
	((Slider*)m_LayerGuiPtr->getModel("ColorGSlider"))->setValue(0.0f);
	((Slider*)m_LayerGuiPtr->getModel("ColorBSlider"))->setValue(0.0f);
	//((Player*)m_Layer3DPtr->getModel("Player"))->setColor(vec3(0.0f,0.0f,1.0f));
}

void MenuGui::next() {
	vector<PlayerSettings*>* list = SettingsManager::Instance->getPlayerSettings();
	SettingsManager::Instance->setSelectedPlayerndex((SettingsManager::Instance->getSelectedPlayerIndex())%(*list).size() + 1);

	Player* player = (Player*)m_Layer3DPtr->getModel("Player");
	if (player != nullptr) {
		PlayerSettings* ps = (*(SettingsManager::Instance->getPlayerSettings()))[SettingsManager::Instance->getSelectedPlayerIndex() - 1];
		player->setColor(ps->getColor());
		player->setScale(ps->getSize());
	}
}

void MenuGui::previous() {
	vector<PlayerSettings*>* list = SettingsManager::Instance->getPlayerSettings();
	SettingsManager::Instance->setSelectedPlayerndex((SettingsManager::Instance->getSelectedPlayerIndex() - 2 + (*list).size()) % (*list).size() + 1);

	Player* player = (Player*)m_Layer3DPtr->getModel("Player");
	if (player != nullptr) {
		PlayerSettings* ps = (*(SettingsManager::Instance->getPlayerSettings()))[SettingsManager::Instance->getSelectedPlayerIndex() - 1];
		player->setColor(ps->getColor());
		player->setScale(ps->getSize());
	}
}



//////// State create character
void MenuGui::stateCreateCharacterIn() {
	state = CREATE_CHARACTER;

	RawModel2D* backButton = m_LayerGuiPtr->getModel("Back");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(backButton, &RawModel2D::setPosition, backButton->getPosition(), vec2(0.45f, -0.55f), 40));

	RawModel2D* createCharacterButton = m_LayerGuiPtr->getModel("CreateCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(createCharacterButton, &RawModel2D::setPosition, createCharacterButton->getPosition(), vec2(-0.85f, -0.75f), 40));

	RawModel2D* sizeSlider = m_LayerGuiPtr->getModel("SizeSlider");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(sizeSlider, &RawModel2D::setPosition, sizeSlider->getPosition(), vec2(-0.85f, -0.5f), 40));

	RawModel2D* colorRSlider = m_LayerGuiPtr->getModel("ColorRSlider");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(colorRSlider, &RawModel2D::setPosition, colorRSlider->getPosition(), vec2(-0.85f, -0.35f), 40));
	RawModel2D* colorGSlider = m_LayerGuiPtr->getModel("ColorGSlider");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(colorGSlider, &RawModel2D::setPosition, colorGSlider->getPosition(), vec2(-0.85f, -0.2f), 40));
	RawModel2D* colorBSlider = m_LayerGuiPtr->getModel("ColorBSlider");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(colorBSlider, &RawModel2D::setPosition, colorBSlider->getPosition(), vec2(-0.85f, -0.05f), 40));
}

void MenuGui::stateCreateCharacterOut() {
	RawModel2D* createCharacterButton = m_LayerGuiPtr->getModel("CreateCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(createCharacterButton, &RawModel2D::setPosition, createCharacterButton->getPosition(), vec2(-2.0f, -0.75f), 40));

	RawModel2D* sizeSlider = m_LayerGuiPtr->getModel("SizeSlider");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(sizeSlider, &RawModel2D::setPosition, sizeSlider->getPosition(), vec2(-2.0f, -0.5f), 40));

	RawModel2D* colorRSlider = m_LayerGuiPtr->getModel("ColorRSlider");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(colorRSlider, &RawModel2D::setPosition, colorRSlider->getPosition(), vec2(-2.0f, -0.35f), 40));
	RawModel2D* colorGSlider = m_LayerGuiPtr->getModel("ColorGSlider");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(colorGSlider, &RawModel2D::setPosition, colorGSlider->getPosition(), vec2(-2.0f, -0.2f), 40));
	RawModel2D* colorBSlider = m_LayerGuiPtr->getModel("ColorBSlider");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(colorBSlider, &RawModel2D::setPosition, colorBSlider->getPosition(), vec2(-2.0f, -0.05f), 40));
}

// Functions
void  MenuGui::createCharacter() {
	Slider* slider = (Slider*)m_LayerGuiPtr->getModel("SizeSlider");
	int ind = (SettingsManager::Instance->getPlayerSettings()->size()) + 1;
	string name = "Teszt" + to_string(ind);
	SettingsManager::Instance->addPlayerSettings(new PlayerSettings(name,
		vec3(
		((Slider*)m_LayerGuiPtr->getModel("ColorRSlider"))->getValue(),
			((Slider*)m_LayerGuiPtr->getModel("ColorGSlider"))->getValue(),
			((Slider*)m_LayerGuiPtr->getModel("ColorBSlider"))->getValue()
		),
		vec3(slider->getValue())
	));
	SettingsManager::Instance->setSelectedPlayerndex(SettingsManager::Instance->getPlayerSettings()->size());
	stateSelectCharacterIn();
	stateCreateCharacterOut();
}



