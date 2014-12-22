
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstdlib>

#include "glimac/Texture.hpp"

namespace glimac {
	Texture Texture::load(std::string path) {
		std::string complete_path = ("../assets/textures/" + path);
        
        SDL_Surface* pTexture = IMG_Load(complete_path.c_str());
        if (!pTexture) {
            std::cerr << "Error loading " << complete_path << std::endl;
            exit(EXIT_FAILURE);
        }

        Texture texture;
        glGenTextures(1, &(texture.tex_id));

        glBindTexture(GL_TEXTURE_2D, texture.tex_id);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pTexture->w, pTexture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, pTexture->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        SDL_FreeSurface(pTexture);

        return texture;
    }

	void Texture::free(){
		glDeleteTextures(1, &tex_id);
	}

    GLuint Texture::getId() const {
        return tex_id;
    }
}