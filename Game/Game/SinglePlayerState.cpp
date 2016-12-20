#include "SinglePlayerState.h"

#include <math.h>

#include "StateManager.h"
#include "Window.h"
#include "Planet.h"
#include "SkyBox.h"
#include "ShaderProgram.h"
#include "Entity.h"
#include "SettingsManager.h"
#include "Player.h"

SinglePlayerState::SinglePlayerState():
	m_BlockCount(5),
	m_BlockSize(75),
	m_SpriteSize(5.0f)
{
	init();
	load();
}

void SinglePlayerState::init() {
	// GUI Layer
	ShaderProgram* shader2d = new ShaderProgram("gui");
	shader2d->enable();
	GLint textures[32];
	for (int i = 0; i < 32; ++i) textures[i] = i;
	shader2d->setUniformiv("textures", textures, 32);
	shader2d->disable();
	m_LayerGui.setShader(shader2d);

	// Sky Layer
	mat4 perspectiveMatrix = mat4::perspective(70, Window::GetInstance()->getWidth()*1.0f / Window::GetInstance()->getHeight(), 0.1f, 1000);
	ShaderProgram* shaderSky = new ShaderProgram("sky");
	shaderSky->enable();
	shaderSky->setUniformMat4("pr_matrix", perspectiveMatrix);
	shaderSky->setUniform1i("SkyGradient", 0);
	shaderSky->setUniform1i("SkyBoxTexture", 1);
	shaderSky->setUniform1i("sunTexture", 2);
	shaderSky->setUniform1i("moonTexture", 3);
	shaderSky->disable();
	m_LayerSky.setShader(shaderSky);

	// 3D static object Layer
	ShaderProgram* shader3d = new ShaderProgram("simple");
	shader3d->enable();
	shader3d->setUniformMat4("pr_matrix", perspectiveMatrix);
	shader3d->setUniform1i("SkyGradient", 0);
	shader3d->disable();
	m_Layer3DStatic = new Layer3DStatic**[m_BlockCount];
	for (int i = 0; i < m_BlockCount; ++i) {
		m_Layer3DStatic[i] = new Layer3DStatic*[m_BlockCount];
		for (int j = 0; j < m_BlockCount; ++j) {
			m_Layer3DStatic[i][j] = new Layer3DStatic();
			m_Layer3DStatic[i][j]->setShader(shader3d);
		}
	}
	m_Layer3DDynamic.setShader(shader3d);
}

void SinglePlayerState::load() {
	// Sky object
	m_LayerSky.addEntity("SkyBox", new SkyBox(TextureCube::get("galaxy.png")));
	m_LayerSky.addEntity("Sun", new Planet(Texture2D::get("sun.png"), 100.0f, vec3(), 5.0f));
	m_LayerSky.addEntity("Moon", new Planet(Texture2D::get("moon.png"), 100.0f, vec3(180.0f, 0.0f, 0.0f), 4.0f));

	m_MainCameraPtr = shared_ptr<Camera>(new Camera());
	m_MainCameraPtr->setCurrentCamera();

	int ind = SettingsManager::Instance->getSelectedPlayerIndex();
	PlayerSettings* playerSettigs = (*SettingsManager::Instance->getPlayerSettings())[ind - 1];
	Player* player = new Player(100.0f, vec3(10.0f, Terrain::getHeight(m_Environment.getSeed(),10.f,10.0f,5.0f), 10.0f), vec3(), playerSettigs->getSize());
	player->setColor(playerSettigs->getColor());
	m_Layer3DDynamic.addModel("Player", player);
	m_MainCameraPtr->setEntity(player);

	m_Environment.setSeed(12345);
	m_PosX = 0;
	m_PosZ = 0;

	for (int i = m_PosX; i < m_BlockCount; ++i) {
		for (int j = m_PosZ; j < m_BlockCount; ++j) {
			m_Layer3DStatic[i][j]->addEntity("Terrain", new Terrain(i - (m_BlockCount / 2), j - (m_BlockCount / 2), m_Environment.getSeed(), m_SpriteSize, m_BlockSize));
		}
	}

	
}

SinglePlayerState::~SinglePlayerState() {
	for (int i = 0; i < m_BlockCount; ++i) {
		for (int j = 0; j < m_BlockCount; ++j) {
			delete m_Layer3DStatic[i][j];
		}
		delete m_Layer3DStatic[i];
	}
	delete m_Layer3DStatic;
}

void SinglePlayerState::resume() {
	m_Environment.setTime(50.0f);
	m_Environment.setTimeSpeed(0.01f);
}

void SinglePlayerState::pause() {
	Window::GetInstance()->setMouseVisibility(true);
}

void SinglePlayerState::update() {
	m_Environment.update();

	m_MainCameraPtr->update();
	updateTerrain();

	if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_ESCAPE)) {
		StateManager::getInstance().closeCurrentState();
	}
	if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_Z)) {
		Window::GetInstance()->setMouseVisibility(false);
	}
	if (Window::GetInstance()->getKeyboarPressed(GLFW_KEY_X)) {
		Window::GetInstance()->setMouseVisibility(true);
	}

	m_Layer3DDynamic.udate();
}

void SinglePlayerState::updateTerrain() {
	vec3 pos = Camera::Current->getPosition();
	int newX = pos.x / (m_BlockSize * m_SpriteSize) - (pos.x < 0 ? 1 : 0);
	int newZ = pos.z / (m_BlockSize * m_SpriteSize) - (pos.z < 0 ? 1 : 0);
	if (newX != m_PosX) {
		if (newX > m_PosX) {  // +X
			for (int i = 0; i < m_BlockCount; ++i) {
				m_Layer3DStatic[0][i]->addEntity("Terrain", new Terrain((m_PosX+ m_BlockCount) - (m_BlockCount / 2), (m_PosZ+i) - (m_BlockCount / 2), m_Environment.getSeed(), m_SpriteSize, m_BlockSize));
			}
			for (int i = 1; i < m_BlockCount; ++i) {
				for (int j = 0; j < m_BlockCount; ++j) {
					Layer3DStatic* tmp = m_Layer3DStatic[i - 1][j];
					m_Layer3DStatic[i - 1][j] = m_Layer3DStatic[i][j];
					m_Layer3DStatic[i][j] = tmp;
				}
			}
			++m_PosX;
		}
		else {				  // -X
			for (int i = 0; i < m_BlockCount; ++i) {
				m_Layer3DStatic[m_BlockCount-1][i]->addEntity("Terrain", new Terrain((m_PosX - 1) - (m_BlockCount / 2), (m_PosZ + i) - (m_BlockCount / 2), m_Environment.getSeed(), m_SpriteSize, m_BlockSize));
			}
			for (int i = m_BlockCount - 2; i >= 0 ; --i) {
				for (int j = 0; j < m_BlockCount; ++j) {
					Layer3DStatic* tmp = m_Layer3DStatic[i + 1][j];
					m_Layer3DStatic[i + 1][j] = m_Layer3DStatic[i][j];
					m_Layer3DStatic[i][j] = tmp;
				}
			}
			--m_PosX;
		}
	} else if (newZ != m_PosZ) {
		if (newZ > m_PosZ) {  // +z
			for (int i = 0; i < m_BlockCount; ++i) {
				m_Layer3DStatic[i][0]->addEntity("Terrain", new Terrain((m_PosX + i) - (m_BlockCount / 2), (m_PosZ + m_BlockCount) - (m_BlockCount / 2), m_Environment.getSeed(), m_SpriteSize, m_BlockSize));
			}
			for (int i = 0; i < m_BlockCount; ++i) {
				for (int j = 1; j < m_BlockCount; ++j) {
					Layer3DStatic* tmp = m_Layer3DStatic[i][j-1];
					m_Layer3DStatic[i][j-1] = m_Layer3DStatic[i][j];
					m_Layer3DStatic[i][j] = tmp;
				}
			}
			++m_PosZ;
		}
		else {				  // -z
			for (int i = 0; i < m_BlockCount; ++i) {
				m_Layer3DStatic[i][m_BlockCount - 1]->addEntity("Terrain", new Terrain((m_PosX + i) - (m_BlockCount / 2), (m_PosZ - 1) - (m_BlockCount / 2), m_Environment.getSeed(), m_SpriteSize, m_BlockSize));
			}
			for (int i = 0; i < m_BlockCount; ++i) {
				for (int j = m_BlockCount - 2; j >= 0 ; --j) {
					Layer3DStatic* tmp = m_Layer3DStatic[i][j+1];
					m_Layer3DStatic[i][j+1] = m_Layer3DStatic[i][j];
					m_Layer3DStatic[i][j] = tmp;
				}
			}
			--m_PosZ;
		}
	} 
}

void SinglePlayerState::render() {
	mat4 roationMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	if (Camera::Current != nullptr) {
		roationMatrix = Camera::Current->getRotationMatrix();
		viewMatrix = Camera::Current->getMatrix();
	}

	// Sky 
	ShaderProgram* shaderSky = m_LayerSky.getShader();
	shaderSky->enable();
		shaderSky->setUniformMat4("vw_matrix", roationMatrix);
		shaderSky->setUniformMat4("rot_matrix", mat4::rotation(m_Environment.getTime(), -1, 0, 0));
		shaderSky->setUniform3f("sunPosition", m_Environment.getSunDirection());
		shaderSky->setUniform1f("time", m_Environment.getTime());
	shaderSky->disable();
	m_LayerSky.render();

	// Static and dynamic
	ShaderProgram* shader3d = m_Layer3DDynamic.getShader();
	shader3d->enable();
		shader3d->setUniformMat4("vw_matrix", viewMatrix);
		shader3d->setUniform3f("sunPosition", m_Environment.getSunDirection());
		shader3d->setUniform1f("time", m_Environment.getTime());
	shader3d->disable();
	for (int i = 0; i < m_BlockCount; ++i)
		for (int j = 0; j < m_BlockCount; ++j)
			m_Layer3DStatic[i][j]->render();
	m_Layer3DDynamic.render();

	// Gui
	m_LayerGui.render();
}