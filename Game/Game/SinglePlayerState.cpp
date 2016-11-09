#include "SinglePlayerState.h"

SinglePlayerState::SinglePlayerState():
	m_SkyShader(ShaderProgram("sky"))
{
	m_SkyRender.submit(m_SkyBox);

	m_SkyShader.enable();
	m_SkyShader.setUniformMat4("pr_matrix", mat4::perspective(70, 960.0 / 540.0, 0.1f, 1000));
	m_SkyShader.setUniform1i("SkyColors", 0);
	m_SkyShader.setUniform1i("SkyBoxTexture", 1);
	m_SkyShader.setUniform1i("sunTexture", 2);
	m_SkyShader.setUniform1i("moonTexture", 3);
	m_SkyShader.disable();
}

SinglePlayerState::~SinglePlayerState() {

}

void SinglePlayerState::update() {
	if (Window::getInstance().keyPressed(GLFW_KEY_ESCAPE)) {
		StateManager::getInstance().popState();
	}

	if (Window::getInstance().keyPressed(GLFW_KEY_Q)) {
		tmp1 += 0.5;
	}
	if (Window::getInstance().keyPressed(GLFW_KEY_W)) {
		tmp2 += 0.5;
	}
}

void SinglePlayerState::render() {
	m_SkyShader.enable();
	m_SkyShader.setUniformMat4("vw_matrix", mat4::rotation(tmp1, 1, 0, 0)*mat4::rotation(tmp2, 0, 1, 0));
	m_SkyRender.flush();
	m_SkyShader.disable();
}