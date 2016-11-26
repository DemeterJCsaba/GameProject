#include "SinglePlayerState.h"

SinglePlayerState::SinglePlayerState():
	m_SkyShader(ShaderProgram("sky")),
	m_Terrain(Terrain(12345,5)),
	m_TerrainRenderer(TerrainRenderEngine(64)),
	m_Shader(ShaderProgram("simple"))
{
	m_SkyRender.submit(m_SkyBox);

	m_SkyShader.enable();
	m_SkyShader.setUniformMat4("pr_matrix", mat4::perspective(70, 960.0f / 540.0f, 0.1f, 1000));
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
	/*
	cout << m_Terrain.getHeight(5, 14) << endl;
	cout << m_Terrain.getHeight(5, 14) << endl;
	cout << m_Terrain.getHeight(5, 14) << endl;

	cout << m_Terrain.getHeight(5, 15) << endl;
	cout << m_Terrain.getHeight(5, 16) << endl;
	cout << m_Terrain.getHeight(5, 17) << endl;
	cout << m_Terrain.getHeight(5, 18) << endl;*/
}

SinglePlayerState::~SinglePlayerState() {
}

void SinglePlayerState::update() {
	m_SunPosition = vec3(0, sin(toRadian(m_Time)), cos(toRadian(m_Time)));
	m_Time = m_Time + 0.2;
	m_Time = m_Time > 360 ? m_Time - 360 : m_Time;

	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_ESCAPE)) {
		StateManager::getInstance().popState();
	}

	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_Z)) {
		Window::getInstance().setMouseVisibility(false);
	}
	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_X)) {
		Window::getInstance().setMouseVisibility(true);
	}

	Camera::current->update();
	//Camera::current->tmp(vec3(0, 0, 0), vec3(Window::getInstance().getMouseOffsetY(), Window::getInstance().getMouseOffsetX(), 0));
	
	//if(Window::getInstance().getMouseOffsetX()!=0 || Window::getInstance().getMouseOffsetY()!=0)
	//	cout << Window::getInstance().getMouseOffsetX() << " - " << Window::getInstance().getMouseOffsetY() << endl;
	/*double x = Window::getInstance().getMousePosX();
	double y = Window::getInstance().getMousePosY();
	Camera::current->tmp(vec3(0,0,0),vec3((-tmpy+y),(tmpx-x),0));
	tmpx = x;
	tmpy = y;*/
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
	m_SkyRender.flush();
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