#include "Window.h"

Window& Window::getInstance() {
	static Window s_Instance(SettingsManager::getWindowWidth(), 
							 SettingsManager::getWindowHeight(),
							 SettingsManager::getWindowTitle(),
							 SettingsManager::getWindowFullScreen());
	return s_Instance;
}

Window::Window(unsigned int width,unsigned int height,string title, bool fullScreen):
	m_Width(width),m_Height(height),m_Title(title),m_FullScreen(fullScreen)
{
	if (!init()) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	for (int i = 0; i < MAX_KEYS; ++i) {
		m_KeyboardButtons[i] = false;
	}
	for (int i = 0; i < MAX_BUTTONS; ++i) {
		m_MouseButtons[i] = false;
	}
	m_MouseX = m_MouseY = m_MouseOffsetX = m_MouseOffsetY = m_MouseWheelOffset = 0;
	m_MouseVisible = true;
}

Window::~Window() {
	Close();
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	return true;
}

void Window::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update() {
	if (m_MouseVisible) {
		m_MouseOffsetX = 0;
		m_MouseOffsetY = 0;
	}
	else {
		cout << m_MouseX << " - " << (m_Width / 2) << " | " << m_MouseY << " - " << (m_Height / 2) << endl;
		m_MouseOffsetX = m_MouseX - (m_Width / 2);
		m_MouseOffsetY = m_MouseY - (m_Height / 2);
		if(m_MouseX!=(m_Width / 2) || m_MouseY!=(m_Height / 2))
			glfwSetCursorPos(m_Window, m_Width / 2, m_Height / 2);
		/*else if (m_MouseX != (m_Width / 2) && m_MouseY == (m_Height / 2))
			glfwSetCursorPos(m_Window, m_Width / 2, m_MouseX);
		else if (m_MouseX == (m_Width / 2) && m_MouseY != (m_Height / 2))
			glfwSetCursorPos(m_Window, m_MouseY, m_Height / 2);*/
	}
}

void Window::Draw() {
	GetError();

	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::Close() {
	if (m_Window != nullptr) {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		m_Window = nullptr;
	}
}

bool Window::IsClosed() const {
	return glfwWindowShouldClose(m_Window) == 1;
}

void Window::GetError(){
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
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseButtons[button] = (action != GLFW_RELEASE);
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