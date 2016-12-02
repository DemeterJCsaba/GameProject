#include "SinglePlayerState.h"

SinglePlayerState::SinglePlayerState():
	m_SkyBoxRenderer(RenderEngine3DTextured(true,16)),
	m_SkyShader(ShaderProgram("sky")),
	m_Terrain(Terrain(12345,5)),
	m_TerrainRenderer(TerrainRenderEngine(150)),
	m_Shader(ShaderProgram("tmp")),
	m_Camera(Camera(&m_Terrain))
{
	m_SkyBoxRenderer.begin();
	m_SkyBoxRenderer.addTexture(new Texture2D("Resources\\Images\\SkyGradient.png"));
	m_SkyBoxRenderer.submit(m_SkyBox.getSkyModel());
	m_SkyBoxRenderer.submit(m_SkyBox.getSunModel());
	m_SkyBoxRenderer.submit(m_SkyBox.getMoonModel());
	m_SkyBoxRenderer.end();

	m_SkyShader.enable();
	m_SkyShader.setUniformMat4("pr_matrix", mat4::perspective(70, Window::getInstance().getWidth()*1.0f/ Window::getInstance().getHeight(), 0.1f, 1000));
	m_SkyShader.setUniform1i("SkyGradient", 0);
	m_SkyShader.setUniform1i("SkyBoxTexture", 1);
	m_SkyShader.setUniform1i("sunTexture", 2);
	m_SkyShader.setUniform1i("moonTexture", 3);
	m_SkyShader.disable();

	m_Camera.setCurrentCamera();

	m_Time = 45;

	m_TerrainRenderer.submit(&m_Terrain,vec2(0,0));

	m_Shader.enable();
	m_Shader.setUniformMat4("pr_matrix", mat4::perspective(70, 960.0f / 540.0f, 0.1f, 1000));
	m_Shader.setUniform1i("SkyGradient", 0);
	m_Shader.disable();
	
	cout << m_Terrain.getHeight(5, 14) << endl;
	cout << m_Terrain.getHeight(5, 14) << endl;
	cout << m_Terrain.getHeight(5, 14) << endl;

	cout << m_Terrain.getHeight(5, 15) << endl;
	cout << m_Terrain.getHeight(5, 16) << endl;
	cout << m_Terrain.getHeight(5, 17) << endl;
	cout << m_Terrain.getHeight(5, 18) << endl;
}

SinglePlayerState::~SinglePlayerState() {
	Window::getInstance().setMouseVisibility(true);
}

void SinglePlayerState::update() {
	m_SunPosition = vec3(0, sin(toRadian(m_Time)), cos(toRadian(m_Time)));
	m_Time = m_Time + 0.0002;
	m_Time = m_Time > 360 ? m_Time - 360 : m_Time;

	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_ESCAPE)) {
		StateManager::getInstance().closeCurrentState();
	}

	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_Z)) {
		Window::getInstance().setMouseVisibility(false);
	}
	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_X)) {
		Window::getInstance().setMouseVisibility(true);
	}

	Camera::current->update();
}

void SinglePlayerState::render() {
	// SkyBox
	m_SkyShader.enable();
	if (Camera::current != nullptr) {
		m_SkyShader.setUniformMat4("vw_matrix", Camera::current->getRotationMatrix());
	}
	m_SkyShader.setUniformMat4("rot_matrix", mat4::rotation(m_Time,-1,0,0));
	m_SkyShader.setUniform3f("sunPosition", m_SunPosition);
	m_SkyShader.setUniform1f("time", m_Time);
	//m_SkyRender.flush();
	m_SkyBoxRenderer.flush();
	m_SkyShader.disable();

	// Terrain
	m_Shader.enable();
	if (Camera::current != nullptr) {
		m_Shader.setUniformMat4("vw_matrix", Camera::current->getMatrix());
	}
	m_Shader.setUniform3f("sunPosition", m_SunPosition);
	m_Shader.setUniform1f("time", m_Time);
	m_TerrainRenderer.flush(Camera::current->getVerPos());
	m_Shader.disable();
}

void SinglePlayerState::resume() {

}

void SinglePlayerState::pause() {

}