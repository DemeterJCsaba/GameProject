#include "SettingsManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

// Settings file name
const string SettingsManager::SettingsFileName = "Settings.txt";

// Load setting from file
void SettingsManager::loadSettings() {
	try {
		ifstream SettingsFile(SettingsFileName);
		if (!SettingsFile.good()) {
			saveSettings();
			SettingsFile = ifstream(SettingsFileName);
		}
		string line;
		while (getline(SettingsFile, line)) {
			istringstream iss(line);
			string key, value;
			iss >> key >> value;
			if (key == "Window_Width:") {
				m_WindowSettings.setWidth(stoi(value));
			}
			else if (key == "Window_Height:") {
				m_WindowSettings.setHeight(stoi(value));
			}
			else if (key == "Window_FullScreen:") {
				m_WindowSettings.setFullScreen(stoi(value));
			}
		}

		SettingsFile.close();
	}
	catch (exception& e) { 
		cout << "Faild to load game setting: " << e.what() << endl;
	} 
}

// Save setting to file
void SettingsManager::saveSettings() {
	ofstream SettingsFile(SettingsFileName);
	
	// Window settings
	SettingsFile << "Window_Width: " << m_WindowSettings.getWidth() << endl;
	SettingsFile << "Window_Height: " << m_WindowSettings.getHeight() << endl;
	SettingsFile << "Window_FullScreen: " << m_WindowSettings.isFullScreen() << endl;
	
	SettingsFile.close();
}