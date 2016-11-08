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
		m_Keys[i] = false;
	}
	for (int i = 0; i < MAX_BUTTONS; ++i) {
		m_Buttons[i] = false;
	}
	m_MouseX = m_MouseY = m_MouseWheelOffset = 0;
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

	glfwSwapInterval(0.0);
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

void Window::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() {
	getError();

	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::close() {
	this->~Window();
}

bool Window::isClosed() const {
	return glfwWindowShouldClose(m_Window) == 1;
}

void Window::getError()
{
	m_Error = glGetError();
	if (m_Error != GL_NO_ERROR) {
		printf("OpenGl Error: %d\n", m_Error);
	}
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
	win->m_Keys[key] = (action != GLFW_RELEASE);
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Buttons[button] = (action != GLFW_RELEASE);
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