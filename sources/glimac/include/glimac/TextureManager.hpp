
#ifndef HPP_TEXTUREMANAGER
#define HPP_TEXTUREMANAGER

#include <map>
#include <string>

#include "Texture.hpp"

namespace glimac {
	class TextureManager: public std::map<std::string, Texture> {
	public:
		const Texture& get(std::string path);

		//~TextureManager();
		void deleteTexture();
	};
}

#endif
