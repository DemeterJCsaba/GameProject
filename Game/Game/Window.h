#pragma once

#include <iostream>
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#define MAX_KEYS	512
#define MAX_BUTTONS 8

using namespace std;

class Window {
private:
	int m_Width;
	int m_Height;
	char* m_Title;
	bool m_FullScreen;

	GLFWwindow* m_Window;
	GLenum m_Error;

	bool m_Keys[MAX_KEYS];
	bool m_Buttons[MAX_BUTTONS];
	double m_MouseX;
	double m_MouseY;
	double m_MouseWheelOffset;
public:
	Window(int width, int height, char* title,bool fullScreen = false);
	~Window();

	void clear() const;
	void update();
	void close();
	bool isClosed() const;
	void getError();

	bool keyPressed(unsigned int keycode) const { return m_Keys[keycode]; }
	bool buttonPressed(unsigned int buttoncode) const { return m_Buttons[buttoncode]; }
	void getMousePos(double* x, double* y) const { *x = m_MouseX; *y = m_MouseY; }
	double getMouseWheel() { return m_MouseWheelOffset; }
private:
	bool init();

	friend static void window_resize(GLFWwindow *window, int width, int height);
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};


