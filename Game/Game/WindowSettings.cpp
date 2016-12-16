#include "WindowSettings.h"

const string WindowSettings::GAME_TITLE = "The Game";

WindowSettings::WindowSettings():
	m_Width(DEFAULT_WIDTH),
	m_Height(DEFAULT_HEIGHT),
	m_IsFullScreen(DEFAULT_ISFULLSCREEN)
{

}

WindowSettings::WindowSettings(unsigned int width, unsigned int height, bool isFullScreen) :
	m_Width(width),
	m_Height(height),
	m_IsFullScreen(isFullScreen)
{
	
}

void WindowSettings::setWidth(unsigned int width) { 
	m_Width = (width >= MIN_WIDTH ? width : MIN_WIDTH); 
}

void WindowSettings::setHeight(unsigned int height) { 
	m_Height = (height >= MIN_HEIGHT ? height : MIN_HEIGHT); 
}

void WindowSettings::setFullScreen(bool fullScreen) { 
	m_IsFullScreen = fullScreen; 
}