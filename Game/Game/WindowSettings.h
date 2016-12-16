#ifndef WINDOWSETTINGS_H
#define WINDOWSETTINGS_H

#include <string>

using namespace std;

class WindowSettings {
private:
	static const unsigned int DEFAULT_WIDTH = 960;
	static const unsigned int MIN_WIDTH = 640;
	static const unsigned int DEFAULT_HEIGHT = 540;
	static const unsigned int MIN_HEIGHT = 480;
	static const string GAME_TITLE;
	static const bool DEFAULT_ISFULLSCREEN = false;

	unsigned int m_Width;
	unsigned int m_Height;
	bool m_IsFullScreen;
public:
	WindowSettings();
	WindowSettings(unsigned int width,unsigned int height,bool isFullScreen);

	// Getters
	unsigned int getWidth() const { return m_Width; }
	unsigned int getHeight() const { return m_Height; }
	string getTitle() const { return GAME_TITLE; }
	bool isFullScreen() const { return m_IsFullScreen; }

	// Setters
	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
	void setFullScreen(bool fullScreen);
};

#endif /* WINDOWSETTINGS_H */