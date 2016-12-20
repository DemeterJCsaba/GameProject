#include "Font.h"

#include <fstream>
#include <sstream>

map<string, Font> Font::m_Fonts = map<string, Font>();

string Font::m_Dir = "Resources\\Font\\";

Font* Font::get(string name) {
	if (m_Fonts.find(name) == m_Fonts.end()) {
		m_Fonts[name] = Font(name);
	}
	return &m_Fonts[name];
}

Font::Font(string name) {
	m_FontAtlas = Texture2D::getTexture(name + ".png");

	ifstream in(m_Dir + name + ".fnt");
	string line;
	string tmp, id, xpos, ypos, width, height, xoffset, yoffset, xadvanced, page, chnl;
	
	float atlasWidth = m_FontAtlas->getWidth();
	float atlasHeight = m_FontAtlas->getHeight();

	while (getline(in, line)) {
		istringstream iss(line);

		if (line.length() >= 5 && line.substr(0, 5) == "char ") {
			iss >> tmp >> id >> xpos >> ypos >> width >> height >> xoffset >> yoffset >> xadvanced >> page >> chnl;

			int charId = atoi((id.substr(3)).c_str());
			// position
			m_Position[charId].x = atoi((xpos.substr(2)).c_str()) / atlasWidth;
			m_Position[charId].y = 1.0 - atoi((ypos.substr(2)).c_str()) / atlasHeight;
			// size
			m_Size[charId].x = atoi((width.substr(6)).c_str()) / atlasWidth;
			m_Size[charId].y = -atoi((height.substr(7)).c_str()) / atlasHeight;
			// offset 
			m_Offset[charId].x = atoi((xoffset.substr(8)).c_str()) / atlasWidth;
			m_Offset[charId].y = -atoi((yoffset.substr(8)).c_str()) / atlasHeight;
			// x advanced
			m_XAdvance[charId] = (atoi((xadvanced.substr(9)).c_str()) / atlasWidth)*0.9;
		}
	}
}