#include "SinglePlayerState.h"

SinglePlayerState::SinglePlayerState():
	m_SkyShader(ShaderProgram("sky"))
{
	m_SkyRender.submit(m_SkyBox);

	m_SkyShader.enable();
	m_SkyShader.setUniformMat4("pr_matrix", mat4::perspective(70, 960.0 / 540.0, 0.1f, 1000));
	m_SkyShader.setUniform1i("SkyGradient", 0);
	m_SkyShader.setUniform1i("SkyBoxTexture", 1);
	m_SkyShader.setUniform1i("sunTexture", 2);
	m_SkyShader.setUniform1i("moonTexture", 3);
	m_SkyShader.disable();

	m_Camera.setCurrentCamera();

	m_Time = 0;
}

SinglePlayerState::~SinglePlayerState() {

}

void SinglePlayerState::update() {
	if (Window::getInstance().keyPressed(GLFW_KEY_ESCAPE)) {
		StateManager::getInstance().popState();
	}

	//Camera::current->tmp();
	
	m_SunPosition = vec3(0,sin(toRadian(m_Time)), cos(toRadian(m_Time)));
	m_Time = m_Time + 0.2;
	m_Time = m_Time > 360 ? m_Time - 360 : m_Time;
}

void SinglePlayerState::render() {
	m_SkyShader.enable();
	if (Camera::current != nullptr) {
		m_SkyShader.setUniformMat4("vw_matrix", Camera::current->getMatrix());
	}
	m_SkyShader.setUniform3f("sunPosition", m_SunPosition);
	m_SkyShader.setUniformMat4("rot_matrix", mat4::rotation(m_Time,-1,0,0));
	m_SkyShader.setUniform1f("time", m_Time);
	m_SkyRender.flush();
	m_SkyShader.disable();
}