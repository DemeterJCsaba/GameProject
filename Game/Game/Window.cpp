#include "Window.h"

#include <iostream>

#include "FPSManager.h"
#include "StateManager.h"
#include "KeyboardButtonEvent.h"
#include "MouseButtonEvent.h"


Window* Window::Instance = nullptr;

void Window::CreateWindow(WindowSettings* settings) {
	CloseWindow();
	Instance = new Window(settings->getWidth(),
						  settings->getHeight(),
						  settings->getTitle(),
						  settings->isFullScreen());
}

void Window::CloseWindow() {
	if (Instance != nullptr) {
		delete Instance;
	}
}



Window::Window(unsigned int width,unsigned int height,string title, bool fullScreen):
	m_Width(width),m_Height(height),m_Title(title),m_FullScreen(fullScreen)
{
	if (!init()) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	for (int i = 0; i < MAX_KEYBOARD_BUTTONS; ++i) {
		m_KeyboardButtons[i] = false;
	}
	for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i) {
		m_MouseButtons[i] = false;
	}
	m_MouseX = m_MouseY = m_MouseOffsetX = m_MouseOffsetY = m_MouseWheelOffset = 0;
	m_MouseVisible = true;
	m_Close = false;
}

Window::~Window() {
	if (m_Window != nullptr) {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		m_Window = nullptr;
	}
}

bool Window::init() {
	if (!glfwInit()) {
		cout << "Faild to initalize GLFW!" << endl;
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), m_FullScreen?glfwGetPrimaryMonitor():NULL, NULL);
	if (!m_Window) {
		glfwTerminate();
		cout << "Faild to initalize window!" << endl;
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);

	glfwSetWindowSizeCallback(m_Window, window_resize);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_callback);
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);

	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK) {
		cout << "Faild to initalize GLEW!" << endl;
		return false;
	}
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	return true;
}

void Window::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() {
	FPSManager::getInstance().start("glfwPollEvents");
	glfwPollEvents();
	FPSManager::getInstance().stop("glfwPollEvents");
	if (m_MouseVisible) {
		m_MouseOffsetX = 0;
		m_MouseOffsetY = 0;
	}
	else {
		m_MouseOffsetX = m_MouseX - (m_Width / 2);
		m_MouseOffsetY = m_MouseY - (m_Height / 2);
		if(m_MouseX!=(m_Width / 2) || m_MouseY!=(m_Height / 2))
			glfwSetCursorPos(m_Window, m_Width / 2, m_Height / 2);
	}
}

void Window::render() {
	getError();

	FPSManager::getInstance().start("glfwSwapBuffers");
	glfwSwapBuffers(m_Window);
	FPSManager::getInstance().stop("glfwSwapBuffers");
}

void Window::close() {
	m_Close = true;
}

bool Window::isClosed() const {
	return m_Close || glfwWindowShouldClose(m_Window) == 1;
}

void Window::getError(){
	m_Error = glGetError();
	if (m_Error != GL_NO_ERROR) {
		printf("OpenGl Error: %d\n", m_Error);
	}
}

void Window::setMouseVisibility(bool mod) {
	if (m_MouseVisible && !mod) { // Hide cursor
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		m_OldMouseX = getMousePosX();
		m_OldMouseY = getMousePosY();
		glfwSetCursorPos(m_Window, m_Width / 2, m_Height / 2);
	}
	else if (!m_MouseVisible && mod) { //Show cursor
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPos(m_Window, m_OldMouseX, m_OldMouseY);
	}
	m_MouseVisible = mod;
}



// Event Handlers
void window_resize(GLFWwindow *window, int width, int height) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Width = width;
	win->m_Height = height;
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_KeyboardButtons[key] = (action != GLFW_RELEASE);
	StateManager::addEvent(new KeyboardButtonEvent(key, action));
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseButtons[button] = (action != GLFW_RELEASE);
	StateManager::addEvent(new MouseButtonEvent(button, action));
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseX = xpos;
	win->m_MouseY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseWheelOffset = yoffset;
}