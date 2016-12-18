#include "Text.h"

Text::Text(string text, vec2 position, float fontSize, Font* font):
	RawModel2D(font->getFontAtlas(),position),
	m_Text(text),
	m_FontPtr(font),
	m_FontSize(fontSize)
{
	vec2 starPos;
	int indexCount = 0;

	for (int i = 0; i < m_Text.size(); ++i) {
		char e = m_Text[i];
		vec2 size = m_FontPtr->getSize(e)*m_FontSize;
		vec2 offs = m_FontPtr->getOffset(e)*m_FontSize;

		vec2 a = starPos + offs;
		vec2 b = a + vec2(size.x*0.5f,0.0f);
		vec2 c = a + vec2(size.x*0.5f,size.y);
		vec2 d = a + vec2(0.0f,size.y);
		m_Vertices.push_back(a);
		m_Vertices.push_back(b);
		m_Vertices.push_back(c);
		m_Vertices.push_back(d);

		vec2 pos = m_FontPtr->getPosition(e);
		size = m_FontPtr->getSize(e);
		m_Textures.push_back(pos);
		m_Textures.push_back(pos + vec2(size.x, 0));
		m_Textures.push_back(pos + size);
		m_Textures.push_back(pos + vec2(0, size.y));

		m_IndicesVertex.push_back(indexCount + 0);
		m_IndicesVertex.push_back(indexCount + 1);
		m_IndicesVertex.push_back(indexCount + 2);
		m_IndicesVertex.push_back(indexCount + 0);
		m_IndicesVertex.push_back(indexCount + 2);
		m_IndicesVertex.push_back(indexCount + 3);

		m_IndicesTexture.push_back(indexCount + 0);
		m_IndicesTexture.push_back(indexCount + 1);
		m_IndicesTexture.push_back(indexCount + 2);
		m_IndicesTexture.push_back(indexCount + 0);
		m_IndicesTexture.push_back(indexCount + 2);
		m_IndicesTexture.push_back(indexCount + 3);

		indexCount += 4;
		starPos.x += m_FontPtr->getXAdvanced(e)*m_FontSize*0.5f;
	}
}