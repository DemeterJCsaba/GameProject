#include "MenuGui.h"

#include "Texture2D.h"
#include "RawModel3D.h"
#include "Interpolation.h"
#include "Delay.h"
#include "StateManager.h"
#include "SinglePlayerState.h"
#include "Text.h"
#include "KeyboardButtonEvent.h"

MenuGui::MenuGui(Layer2D* layerGui, Layer3DDynamic* layer3D):
	m_LayerGuiPtr(layerGui),
	m_Layer3DPtr(layer3D)
{
	
}

void MenuGui::load() {
	m_LayerGuiPtr->addModel("Fade",            new GUIImage(vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f), Texture2D::getTexture("Fade.png")));
	m_LayerGuiPtr->addModel("StartButton",     new Button<MenuGui>("Start Game",      vec2(-0.85f, 0.2f),   vec2(0.35f, 0.15f), &MenuGui::startGameButtonExecute, this));
	m_LayerGuiPtr->addModel("ExitButton",      new Button<MenuGui>("Exit Game",       vec2(-0.85f, -0.35f), vec2(0.35f, 0.15f), &MenuGui::exitGame, this));
	m_LayerGuiPtr->addModel("SelectCharacter", new Button<MenuGui>("Select Character",vec2(0.3f, -0.7f),    vec2(0.35f, 0.15f), &MenuGui::selectCaracter, this));
	m_LayerGuiPtr->addModel("Back",            new Button<MenuGui>("Back",            vec2(0.45f, -0.55f),  vec2(0.35f, 0.15f), &MenuGui::backToMain, this));
	m_LayerGuiPtr->addModel("NewCharacter",    new Button<MenuGui>("New Character",   vec2(-0.85f, -0.35f), vec2(0.35f, 0.15f), &MenuGui::createCharater, this));
	m_LayerGuiPtr->addModel("Text", new Text("The Game - v0.1 (alpha)",vec2(-0.9f, -0.9f),0.35f));

	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("StartButton"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("ExitButton"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("SelectCharacter"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("Back"));
	m_GUIManager.addButton((Button<MenuGui>*)m_LayerGuiPtr->getModel("NewCharacter"));
}

void MenuGui::start() {
	m_LayerGuiPtr->getModel("StartButton")->setPosition(vec2(-2.0f, 0.2f));
	m_LayerGuiPtr->getModel("ExitButton")->setPosition(vec2(-2.0f, -0.35f));
	m_LayerGuiPtr->getModel("SelectCharacter")->setPosition(vec2(1.5f, -0.7f));
	m_LayerGuiPtr->getModel("Back")->setPosition(vec2(1.5f, -0.55f));
	m_LayerGuiPtr->getModel("NewCharacter")->setPosition(vec2(-2.0f, -0.75f));
	mainButtonsIn();

	m_TimerManager.addTimer(new Interpolation<MenuGui, float>(this, &MenuGui::fade, 1.0f, 0.0f, 40));
	state = 0;
}

void MenuGui::update() {
	m_TimerManager.update();
}

void MenuGui::handleEvent(Event* event) {
	if (event->getEvent() == Event::EVENTS::KEYBOARD_BUTTON) {
		KeyboardButtonEvent* keyboardEvent = (KeyboardButtonEvent*)event;
		if (keyboardEvent->getKeyCode() == GLFW_KEY_ESCAPE && keyboardEvent->getActionCode() == GLFW_PRESS) {
			backToMain();
		}
	}
	else if (event->getEvent() == Event::EVENTS::MOUSE_BUTTON) {
		MouseButtonEvent* mouseEvent = (MouseButtonEvent*)event;
		m_GUIManager.execute(mouseEvent);
	}
}

void MenuGui::backToMain() {
	if (state == 3) {
		selectCharacterIn();
		state = 2;
	}
	else {
		mainButtonsIn();
		RawModel3D* player = m_Layer3DPtr->getModel("Player");
		m_TimerManager.addTimer(new Interpolation<RawModel3D, vec3>(player, &RawModel3D::setPosition, player->getPosition(), vec3(3.0f, -0.5f, -7.0f), 40));

		Button<MenuGui>* backButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("Back");
		m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(backButton, &Button<MenuGui>::setPosition, backButton->getPosition(), vec2(1.5f, -0.55f), 40));
		selectCharacterOut();
	}
}

void MenuGui::mainButtonsIn() {
	Button<MenuGui>* startButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("StartButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(startButton, &Button<MenuGui>::setPosition, startButton->getPosition(), vec2(-0.85f, 0.2f), 40));

	Button<MenuGui>* exitButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("ExitButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(exitButton, &Button<MenuGui>::setPosition, exitButton->getPosition(), vec2(-0.85f, -0.35f), 40));

	Button<MenuGui>* selectCharacterButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("SelectCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(selectCharacterButton, &Button<MenuGui>::setPosition, selectCharacterButton->getPosition(), vec2(0.3f, -0.7f), 40));
}

void MenuGui::mainButtonsOut() {
	Button<MenuGui>* startButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("StartButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(startButton, &Button<MenuGui>::setPosition, startButton->getPosition(), vec2(-2.0f, 0.2f), 40));

	Button<MenuGui>* exitButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("ExitButton");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(exitButton, &Button<MenuGui>::setPosition, exitButton->getPosition(), vec2(-2.0f, -0.35f), 40));

	Button<MenuGui>* selectCharacterButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("SelectCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(selectCharacterButton, &Button<MenuGui>::setPosition, selectCharacterButton->getPosition(), vec2(1.5f, -0.7f), 40));
}

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
	mainButtonsOut();
	RawModel3D* player = m_Layer3DPtr->getModel("Player");
	m_TimerManager.addTimer(new Interpolation<RawModel3D, vec3>(player, &RawModel3D::setPosition, player->getPosition(), vec3(0.0f, -0.5f, -5.5f), 40));

	Button<MenuGui>* backButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("Back");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(backButton, &Button<MenuGui>::setPosition, backButton->getPosition(), vec2(0.45f, -0.55f), 40));

	selectCharacterIn();
}

void MenuGui::createCharater() {
	selectCharacterOut();
	state = 3;
}

void MenuGui::selectCharacterIn() {
	Button<MenuGui>* newCharacterButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("NewCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(newCharacterButton, &Button<MenuGui>::setPosition, newCharacterButton->getPosition(), vec2(-0.85f, -0.75f), 40));
}

void MenuGui::selectCharacterOut() {
	Button<MenuGui>* newCharacterButton = (Button<MenuGui>*)m_LayerGuiPtr->getModel("NewCharacter");
	m_TimerManager.addTimer(new Interpolation<RawModel2D, vec2>(newCharacterButton, &Button<MenuGui>::setPosition, newCharacterButton->getPosition(), vec2(-2.0f, -0.75f), 40));
}

void MenuGui::fade(float value) {
	ShaderProgram* shader = m_LayerGuiPtr->getShader();
	shader->enable();
	shader->setUniform1f("fade", 1.0f - value);
	shader->disable();
}