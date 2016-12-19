#include "SettingsManager.h"

#include <fstream>
#include <sstream>
#include <iostream>


SettingsManager* SettingsManager::Instance = nullptr;

// Settings file name
const string SettingsManager::SettingsFileName = "Settings.txt";
// Player settings files
const string SettingsManager::PlayerSettingDir = "Resources\\Players\\";

SettingsManager::SettingsManager() {
	Instance = this;
}

SettingsManager::~SettingsManager() {
	for (PlayerSettings* player : m_PlayerSettings) {
		delete player;
	}
}

void SettingsManager::addPlayerSettings(PlayerSettings* player) {
	m_PlayerSettings.push_back(player);
}


void SettingsManager::loadSettings() {
	vector<string> players;
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
			iss >> key;
			if (key == "Window_Width:") {
				iss >> value;
				m_WindowSettings.setWidth(stoi(value));
			}
			else if (key == "Window_Height:") {
				iss >> value;
				m_WindowSettings.setHeight(stoi(value));
			}
			else if (key == "Window_FullScreen:") {
				iss >> value;
				m_WindowSettings.setFullScreen(stoi(value));
			}
			else if (key == "Players:") {
				iss >> value;
				m_SelectedPlayerIndex = stoi(value);
				while (iss >> value) {
					loadPlayerSettings(value);
				}
			}
		}

		SettingsFile.close();
	}
	catch (exception& e) { 
		cout << "Faild to load game setting: " << e.what() << endl;
	}
}

void SettingsManager::loadPlayerSettings(string name) {
	try {
		ifstream PlayerSettingsFile(PlayerSettingDir + name + ".txt");
		if (!PlayerSettingsFile.good()) {
			return;
		}
		string line2;
		string name;
		vec3 color;
		vec3 size;
		while (getline(PlayerSettingsFile, line2)) {
			istringstream iss2(line2);
			string key2, value2;
			iss2 >> key2;
			if (key2 == "Name:") {
				iss2 >> name;
			}
			else if (key2 == "Color:") {
				string c1, c2, c3;
				iss2 >> c1 >> c2 >> c3;
				color = vec3(stof(c1), stof(c2), stof(c3));
			}
			else if (key2 == "Size:") {
				string s1, s2, s3;
				iss2 >> s1 >> s2 >> s3;
				size = vec3(stof(s1), stof(s2), stof(s3));
			}
		}
		m_PlayerSettings.push_back(new PlayerSettings(name, color, size));
	}
	catch (exception& e) {
		cout << "Faild to load game setting: " << e.what() << endl;
	}
}

void SettingsManager::saveSettings() {
	ofstream SettingsFile(SettingsFileName);
	
	// Window settings
	SettingsFile << "Window_Width: " << m_WindowSettings.getWidth() << endl;
	SettingsFile << "Window_Height: " << m_WindowSettings.getHeight() << endl;
	SettingsFile << "Window_FullScreen: " << m_WindowSettings.isFullScreen() << endl;

	SettingsFile << "Players: " << m_SelectedPlayerIndex;
	for (PlayerSettings* player : m_PlayerSettings) {
		SettingsFile << " " << player->getName();

		ofstream PlayerSettingsFile(PlayerSettingDir + player->getName() + ".txt");
		PlayerSettingsFile << "Name: " << player->getName() << endl;
		PlayerSettingsFile << "Color: " << player->getColor().x << " " << player->getColor().y << " " << player->getColor().z << endl;
		PlayerSettingsFile << "Size: " << player->getSize().x << " " << player->getSize().y << " " << player->getSize().z << endl;
		PlayerSettingsFile.close();
	}
	SettingsFile << endl;
	
	SettingsFile.close();
}