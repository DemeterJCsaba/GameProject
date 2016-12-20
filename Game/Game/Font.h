#ifndef FONT_H
#define FONT_H

#include <map>

#include "Texture2D.h"
#include "Maths.h"

using namespace std;

class Font {
private:
	static string m_Dir;
	static map<string, Font> m_Fonts;
public:
	static Font* get(string name);

private:
	Texture2D* m_FontAtlas;
	vec2 m_Position[256];
	vec2 m_Size[256];
	vec2 m_Offset[256];
	float m_XAdvance[256];
	
	
public:
	Font(){}
	Font(string name);
	Texture2D* getFontAtlas() const { return m_FontAtlas; }

	vec2 getPosition(char character)const { return m_Position[character]; }
	vec2 getSize(char character)const { return m_Size[character]; }
	vec2 getOffset(char character)const { return m_Offset[character]; }
	float getXAdvanced(char character)const { return m_XAdvance[character]; }
};

#endif // !FONT_H