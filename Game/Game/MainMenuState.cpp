#include "MainMenuState.h"

#include "Interpolation.h"
#include "Delay.h"
#include "Text.h"
#include "Player.h"

MainMenuState::MainMenuState():
	m_Gui(&m_LayerGui,&m_Layer3DDynamic)
{
	init();
	load();
}

MainMenuState::~MainMenuState() {
	
}

// Initializing shaders and renderers
void MainMenuState::init() {
	// GUI Layer
	ShaderProgram* shader2d = new ShaderProgram("gui");
	shader2d->enable();
	GLint textures[32];
	for (int i = 0; i < 32; ++i) textures[i] = i;
	shader2d->setUniformiv("textures", textures, 32);
	shader2d->disable();
	m_LayerBG.setShader(shader2d);
	m_LayerGui.setShader(shader2d);

	// 3D Layer
	ShaderProgram* shader3d = new ShaderProgram("menu3D");
	shader3d->enable();
	shader3d->setUniformMat4("pr_matrix", mat4::perspective(50.0f, Window::GetInstance()->getWidth()*1.0f / Window::GetInstance()->getHeight(), 0.1f, 1000));
	shader3d->disable();
	m_Layer3DDynamic.setShader(shader3d);
}

// Loading objects
void MainMenuState::load() {
	m_LayerBG.addModel("Fade", new GUIImage(vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f), Texture2D::getTexture("Fade.png")));
	m_LayerBG.addModel("BackGround", new GUIImage(vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f), Texture2D::getTexture("MainMenu_BG.png")));
	
	m_Layer3DDynamic.addModel("Player", new Player(100.0f,vec3(3.0f, -0.5f, -7.0f)));

	m_Gui.load();
}
 


void MainMenuState::update() {
	for (Event* e : m_Events)
		m_Gui.handleEvent(e);
	m_Events.clear();

	m_Gui.update();

	m_Layer3DDynamic.getModel("Player")->addRotate(vec3(0.0f, -0.03f, 0.0f));
	m_Layer3DDynamic.udate();
}

void MainMenuState::render() {
	m_LayerBG.render();
	m_Layer3DDynamic.render();
	m_LayerGui.render();
}



void MainMenuState::resume() {
	cout << "Main menu resume." << endl;

	m_Layer3DDynamic.getModel("Player")->setRotate(vec3(0.0f, -100.0f, 0.0f));
	m_Gui.start();
}

void MainMenuState::pause() {
	cout << "Main menu pause." << endl;
}

