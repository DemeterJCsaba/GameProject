#ifndef WINDOW_H
#define WINDOW_H

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "WindowSettings.h"

using namespace std;

class Window {
private:
	static Window* Instance;
public:
	static void CreateWindow(WindowSettings* settings);
	static void CloseWindow();
	static Window* GetInstance() { return Instance; }

private:
	static const int MAX_KEYBOARD_BUTTONS = 512;
	static const int MAX_MOUSE_BUTTONS = 8;

	int m_Width;
	int m_Height;
	string m_Title;
	bool m_FullScreen;

	GLFWwindow* m_Window;
	GLenum m_Error;

	double m_OldMouseX;
	double m_OldMouseY;
	bool m_MouseVisible;

	bool m_KeyboardButtons[MAX_KEYBOARD_BUTTONS];
	bool m_MouseButtons[MAX_MOUSE_BUTTONS];
	double m_MouseX;
	double m_MouseY;
	double m_MouseWheelOffset;
	double m_MouseOffsetX;
	double m_MouseOffsetY;

	bool m_Close;

	Window(unsigned int width, unsigned int height, string title,bool fullScreen = false);
public:
	~Window();

	void clear() const;
	void update();
	void render();
	void close();
	bool isClosed() const;
	void getError();

	// Getters
	int getWidth() const { return m_Width; }
	int getHeight() const { return m_Height; }

	bool getKeyboarPressed(unsigned int keycode) const { return m_KeyboardButtons[keycode]; }
	bool getMousePressed(unsigned int buttoncode) const { return m_MouseButtons[buttoncode]; }
	double getMousePosX() const { return m_MouseX; }
	double getMousePosY() const { return m_MouseY; }
	double getMouseWheelOffset() const{ return m_MouseWheelOffset; }
	double getMouseOffsetX() const { return m_MouseOffsetX; }
	double getMouseOffsetY() const { return m_MouseOffsetY; }

	void setMouseVisibility(bool mod = true);
private:
	bool init();

	// Event handlers
	friend static void window_resize(GLFWwindow *window, int width, int height);
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif /* WINDOW_H */