#pragma once

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class SettingsManager {
private:
	static const string SettingsFileName;

	// Window Settings
	static unsigned int Window_Width;
	static unsigned int Window_Height;
	static const string Window_Title;
	static bool Window_FullScreen;

	SettingsManager() {}
public:
	static void LoadSettings();
	static void SaveSettings();

	// Getters
	static unsigned int getWindowWidth() { return Window_Width; }
	static unsigned int getWindowHeight() { return Window_Height; }
	static string getWindowTitle() { return Window_Title; }
	static bool getWindowFullScreen() { return Window_FullScreen; }

	// Setters
	static void setWindowWidth(unsigned int width) { Window_Width = (width >= 640 ? width : 640); }
	static void setWindowHeight(unsigned int height) { Window_Height = (height >= 480 ? height : 480); }
	static void setWindowFullScreen(bool fullScreen) { Window_FullScreen = fullScreen; }
};