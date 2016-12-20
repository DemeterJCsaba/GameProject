#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <string>
#include <vector>

#include "WindowSettings.h"
#include "PlayerSettings.h"

using namespace std;

class SettingsManager {
private:
	static const string SettingsFileName;
	static const string PlayerSettingDir;
public:
	static SettingsManager* Instance;

private:
	WindowSettings m_WindowSettings;
	vector<PlayerSettings*> m_PlayerSettings;
	int m_SelectedPlayerIndex;
public:
	SettingsManager();
	~SettingsManager();

	void loadSettings();
	void saveSettings();

	WindowSettings* getWindowSettings() { return &m_WindowSettings; }

	vector<PlayerSettings*>* getPlayerSettings() { return &m_PlayerSettings; }
	void addPlayerSettings(PlayerSettings* player);
	int getSelectedPlayerIndex() const { return m_SelectedPlayerIndex; }
	void setSelectedPlayerndex(int ind) { m_SelectedPlayerIndex = ind; }
private:
	void loadPlayerSettings(string name);
};

#endif /* SETTINGSMANAGER_H */