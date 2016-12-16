#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <string>

#include "WindowSettings.h"

using namespace std;

class SettingsManager {
private:
	static const string SettingsFileName;

	WindowSettings m_WindowSettings;
public:
	SettingsManager() {}

	void loadSettings();
	void saveSettings();

	WindowSettings* getWindowSettings() { return &m_WindowSettings; }
};

#endif /* SETTINGSMANAGER_H */