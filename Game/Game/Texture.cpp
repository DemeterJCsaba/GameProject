#include "Texture.h"

map<string, Texture*> Texture::m_Textures = map<string, Texture*>();

void Texture::clearTextures() {
	for (map<string, Texture*>::iterator i = m_Textures.begin(); i != m_Textures.end(); ++i ) {
		delete i->second;
	}
}

void Texture::deleteTexture(string name) {
	if (m_Textures.find(name) != m_Textures.end())
		m_Textures.erase(name);
}