#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <glimac/Interface.hpp>

namespace glimac {

    void DrawRectangle(int left, int right, int top, int bottom, GLuint texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        //Top-left vertex (corner) 
        glTexCoord2i(0, 0);
        glVertex2f(GLfloat(left), GLfloat(top));

        //Top-right vertex (corner)
        glTexCoord2i(1, 0);
        glVertex2f(GLfloat(right), GLfloat(top));

        //Bottom-right vertex (corner)
        glTexCoord2i(1, 1);
        glVertex2f(GLfloat(right), GLfloat(bottom));

        //Bottom-left vertex (corner)
        glTexCoord2i(0, 1);
        glVertex2f(GLfloat(left), GLfloat(bottom));

        glEnd();
    }

    // void DrawTextGL(int left, int top, TTF_Font* font, std::string text)
    // {
    //     SDL_Color color = {255, 255, 255, 255};
    //     SDL_Surface* textSurface;
    //     textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    //     GLuint Texture = SDLSurfaceToTexture(textSurface);

    //     DrawRectangle(left, left + 260, top, top + 80, Texture);

    //     SDL_FreeSurface(textSurface);
    //     glDeleteTextures(1, &Texture);
    // }

    void DrawImage(int left, int top, int width, int height, const char* filename)
    {
        SDL_Surface *surface; // this surface will tell us the details of the image
        surface = IMG_Load(filename);

        GLuint Texture = SDLSurfaceToTexture(surface);

        DrawRectangle(left, left + width, top, top + height, Texture);

        glDeleteTextures(1, &Texture);

        // Free the SDL_Surface only if it was successfully created
        if ( surface ) {
            SDL_FreeSurface( surface );
        }
    }

    GLuint SDLSurfaceToTexture(SDL_Surface* surface)
    {
        GLuint texture;
        GLint nOfColors;
        GLenum texture_format;

        // Get the number of channels in the SDL surface
        nOfColors = surface->format->BytesPerPixel;

        if (nOfColors == 4)     // contains an alpha channel
        {
            if (surface->format->Rmask == 0x000000ff)
                texture_format = GL_RGBA;
            else
                texture_format = GL_BGRA;
        } 
        else if (nOfColors == 3)
        {
            if (surface->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        }
        else
        {
            printf("Picture with less than 24-bit color depth detected.\n");
            return 0;
        }

        // Have OpenGL generate a texture object handle for us
        glGenTextures(1, &texture);

        // Bind the texture object
        glBindTexture(GL_TEXTURE_2D, texture); 

        // Set the texture's stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
        texture_format, GL_UNSIGNED_BYTE, surface->pixels);

        // Bind the texture to which subsequent calls refer to
        glBindTexture(GL_TEXTURE_2D, texture);

        return texture;
    }

    // void render(std::string text, TTF_Font* font, GLuint texture, int height, int width){

    //     glEnable(GL_TEXTURE_2D);
    //     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //     glViewport(0, 0, 800, 600);

    //     glMatrixMode(GL_PROJECTION);
    //     glLoadIdentity();
    //     glOrtho(0.0f, 800, 600, 0.0f, -1.0f, 1.0f);
    //     glMatrixMode(GL_MODELVIEW);
    //     glLoadIdentity();

    //     // Enabling transparency
    //     glEnable(GL_BLEND);
    //     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    //     DrawTextGL(height, width, font, text);
    // }

}