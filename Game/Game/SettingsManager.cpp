#include "SettingsManager.h"

// Settings file name
const string SettingsManager::SettingsFileName = "Settings.txt";

// Window settings - Default values
unsigned int SettingsManager::Window_Width = 960;
unsigned int SettingsManager::Window_Height = 540;
const string SettingsManager::Window_Title = "Game";
bool SettingsManager::Window_FullScreen = false;

// Load setting from file
void SettingsManager::LoadSettings() {
	ifstream SettingsFile(SettingsFileName);
	if(!SettingsFile.good()) {
		SaveSettings();
		SettingsFile = ifstream(SettingsFileName);
	}
	string line;
	while (getline(SettingsFile, line)) {
		istringstream iss(line);
		string key, value;
		iss >> key >> value;
		if (key == "Window_Width:") {
			setWindowWidth(stoi(value));
		}else if (key == "Window_Height:") {
			setWindowHeight(stoi(value));
		}else if (key == "Window_FullScreen:") {
			setWindowFullScreen(stoi(value));
		}
	}
}

// Save setting to file
void SettingsManager::SaveSettings() {
	ofstream SettingsFile(SettingsFileName);
	SettingsFile << "Window_Width: " << Window_Width << endl;
	SettingsFile << "Window_Height: " << Window_Height << endl;
	SettingsFile << "Window_FullScreen: " << Window_FullScreen << endl;
}