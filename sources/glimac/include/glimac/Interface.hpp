#pragma once

#include <string>
#include <GL/glew.h>

namespace glimac {
	struct Color
	{
	    unsigned char R, G, B, A;

	    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : R(r), G(g), B(b), A(a) {}
	};


	void DrawRectangle(int left, int right, int top, int bottom, GLuint texture);
	// void DrawTextGL(int left, int top, TTF_Font* font, std::string text);
	void DrawImage(int left, int top, int width, int height, const char* filename);
	GLuint SDLSurfaceToTexture(SDL_Surface* surface);
	// void render(std::string text, TTF_Font* font, GLuint texture, int height, int width);

}