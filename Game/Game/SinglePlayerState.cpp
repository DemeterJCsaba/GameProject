#include "SinglePlayerState.h"

SinglePlayerState::SinglePlayerState() {

}

SinglePlayerState::~SinglePlayerState() {

}

void SinglePlayerState::update() {
	if (Window::getInstance().keyPressed(GLFW_KEY_ESCAPE)) {
		StateManager::getInstance().popState();
	}
}

void SinglePlayerState::render() {

}