#include "glimac/TextureManager.hpp"

namespace glimac {

	const Texture& TextureManager::get(std::string path) {
		TextureManager::iterator it = this->find(path);
		if(it == this->end()) {
			Texture resource = Texture::load(path);
			(*this)[path] = resource;
		}

		return (*this)[path];
	}

	void TextureManager::deleteTexture() {
		for(std::map<std::string, Texture>::iterator it = this->begin(); it != this->end(); it++){
			(it->second).free();
		}
	}
}

