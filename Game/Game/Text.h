#ifndef TEXT_H
#define TEXT_H

#include "RawModel2D.h"
#include "Font.h"

class Text : public RawModel2D{
private:
	string m_Text;
	Font* m_FontPtr;
	float m_FontSize;
public:
	Text(string text,vec2 position, float fontSize = 1.0f,Font* font = Font::get("Arial"));

	string getText() { return m_Text; }
};

#endif // !TEXT_H
