#include "SinglePlayerState.h"

SinglePlayerState::SinglePlayerState():
	m_BlockCount(5),
	m_BlockSize(50),
	m_SpriteSize(5.0f)
{
	init();

	// Sky object
	m_LayerSky->addEntity("SkyBox",new SkyBox(new TextureCube("Resources\\Images\\CubeTextures\\galaxy.png")));
	m_LayerSky->addEntity("Sun",new Planet(new Texture2D("Resources\\Images\\sun.png"),100.0f,vec3(),5.0f));
	m_LayerSky->addEntity("Moon", new Planet(new Texture2D("Resources\\Images\\moon.png"), 100.0f, vec3(180.0f,0.0f,0.0f), 4.0f));


	m_Environment.setSeed(12345);
	m_PosX = 0;
	m_PosZ = 0;

	for (int i = m_PosX; i < m_BlockCount; ++i) {
		for (int j = m_PosZ; j < m_BlockCount; ++j) {
			m_Layer3DStatic[i][j]->addEntity("Terrain", new Terrain(i-(m_BlockCount/2), j-(m_BlockCount/2), m_Environment.getSeed(), m_SpriteSize, m_BlockSize));
		}
	}

	m_MainCamera = new Camera();
	m_MainCamera->setCurrentCamera();
}

void SinglePlayerState::init() {
	// GUI Layer
	ShaderProgram* shader2d = new ShaderProgram("gui");
	shader2d->enable();
	GLint textures[32];
	for (int i = 0; i < 32; ++i) textures[i] = i;
	shader2d->setUniformiv("textures", textures, 32);
	shader2d->disable();
	m_LayerGUI = new LayerGUI(shader2d);

	// Sky Layer
	mat4 perspectiveMatrix = mat4::perspective(70, Window::getInstance().getWidth()*1.0f / Window::getInstance().getHeight(), 0.1f, 1000);
	ShaderProgram* shaderSky = new ShaderProgram("sky");
	shaderSky->enable();
	shaderSky->setUniformMat4("pr_matrix", perspectiveMatrix);
	shaderSky->setUniform1i("SkyGradient", 0);
	shaderSky->setUniform1i("SkyBoxTexture", 1);
	shaderSky->setUniform1i("sunTexture", 2);
	shaderSky->setUniform1i("moonTexture", 3);
	shaderSky->disable();
	m_LayerSky = new LayerSky(shaderSky);

	// 3D static object Layer
	ShaderProgram* shader3d = new ShaderProgram("tmp");
	shader3d->enable();
	shader3d->setUniformMat4("pr_matrix", perspectiveMatrix);
	shader3d->setUniform1i("SkyGradient", 0);
	shader3d->disable();
	m_Layer3DStatic = new Layer3DStatic**[m_BlockCount];
	for (int i = 0; i < m_BlockCount; ++i) {
		m_Layer3DStatic[i] = new Layer3DStatic*[m_BlockCount];
		for (int j = 0; j < m_BlockCount; ++j) {
			m_Layer3DStatic[i][j] = new Layer3DStatic(shader3d);
		}
	}
}

SinglePlayerState::~SinglePlayerState() {
	delete m_LayerGUI;
	delete m_LayerSky;

	for (int i = 0; i < m_BlockCount; ++i) {
		for (int j = 0; j < m_BlockCount; ++j) {
			delete m_Layer3DStatic[i][j];
		}
		delete m_Layer3DStatic[i];
	}
	delete m_Layer3DStatic;
}

void SinglePlayerState::resume() {
	m_Environment.setTime(45.0f);
}

void SinglePlayerState::pause() {
	Window::getInstance().setMouseVisibility(true);
}

void SinglePlayerState::update() {
	m_Environment.update();

	m_MainCamera->update();
	updateTerrain();

	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_ESCAPE)) {
		StateManager::getInstance().closeCurrentState();
	}
	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_Z)) {
		Window::getInstance().setMouseVisibility(false);
	}
	if (Window::getInstance().getKeyboarPressed(GLFW_KEY_X)) {
		Window::getInstance().setMouseVisibility(true);
	}
}

void SinglePlayerState::updateTerrain() {
	vec2 pos = Camera::current->getVerPos();
	int newX = pos.x / (m_BlockSize * m_SpriteSize) - (pos.x < 0 ? 1 : 0);
	int newZ = pos.y / (m_BlockSize * m_SpriteSize) - (pos.y < 0 ? 1 : 0);
	//cout << "x: " << newX << " z: " << newZ << endl;
	if (newX != m_PosX) {
		/*int diff = newX - m_PosX;
		for (int i = 0; i < (m_BlockCount-(diff<0?-diff:diff)); ++i) {
			int row = (diff > 0 ? diff + i : i);
			int row2 = row - diff;
			for (int j = 0; j < m_BlockCount; ++j) {
				cout << row << " " << j << " > " << row2 << " " << j << endl;
				Layer3DStatic* tmp = m_Layer3DStatic[row2][j];
				m_Layer3DStatic[row2][j] = m_Layer3DStatic[row][j];
				m_Layer3DStatic[row][j] = tmp;
			}
		}*/
		if (newX > m_PosX) {
			int diff = newX - m_PosX;
			for (int i = 0; i < diff; ++i) {
				for (int j = 0; j < m_BlockCount; ++j) {
					//cout << i << " " << j << " new " << (i + (m_BlockCount - diff) + newX - (m_BlockCount / 2)) << " " << (j + m_PosZ - (m_BlockCount / 2)) << endl;
					m_Layer3DStatic[i][j]->addEntity("Terrain", new Terrain(i + (m_BlockCount - diff) + newX - (m_BlockCount / 2), (j + m_PosZ - (m_BlockCount / 2)), m_Environment.getSeed(), m_SpriteSize, m_BlockSize));
				}
			}

			//assert(diff < m_BlockCount);
			
			for (int i = diff; i < m_BlockCount; ++i) {
				for (int j = 0; j < m_BlockCount; ++j) {
					cout << i << " " << j << " > " << (i-diff) << " " << j << endl;
					Layer3DStatic* tmp = m_Layer3DStatic[i - diff][j];
					m_Layer3DStatic[i - diff][j] = m_Layer3DStatic[i][j];
					m_Layer3DStatic[i][j] = tmp;
				}
			}
		}
		else {
			int diff = m_PosX - newX;
			for (int i = 0; i < diff; ++i) {
				for (int j = 0; j < m_BlockCount; ++j) {
					cout << i << " " << j << " new " << (i + diff - 1 + newX - (m_BlockCount / 2)) << " " << (j + m_PosZ - (m_BlockCount / 2)) << endl;
					//m_Layer3DStatic[i][j]->addEntity("Terrain", new Terrain(i + (m_BlockCount - diff) + newX - (m_BlockCount / 2), (j + m_PosZ - (m_BlockCount / 2)), m_Seed, 5, 150));
				}
			}
			/*for (int i = diff; i >= 0 ; --i) {
				for (int j = 0; j < m_BlockCount; ++j) {
					cout << i << " " << j << " > " << (i - diff) << " " << j << endl;
					Layer3DStatic* tmp = m_Layer3DStatic[i - diff][j];
					m_Layer3DStatic[i - diff][j] = m_Layer3DStatic[i][j];
					m_Layer3DStatic[i][j] = tmp;
				}
			}*/
		}
		m_PosX = newX;
	}
	else if (newZ != m_PosZ) {

	}
}

void SinglePlayerState::render() {
	mat4 roationMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	if (Camera::current != nullptr) {
		roationMatrix = Camera::current->getRotationMatrix();
		viewMatrix = Camera::current->getMatrix();
	}

	m_LayerGUI->render();
	m_LayerSky->render(roationMatrix,m_Environment.getTime(), m_Environment.getSunDirection());
	for (int i = 0; i < m_BlockCount; ++i)
		for (int j = 0; j < m_BlockCount; ++j)
			m_Layer3DStatic[i][j]->render(viewMatrix, m_Environment.getTime(), m_Environment.getSunDirection());
}