#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "glimac/Program.hpp"
#include "glimac/TextureManager.hpp"

static const Uint32 FPS = 30;
static const Uint32 FRAME_DURATION = 1000.f / FPS;

static const Uint32 WINDOW_WIDTH = 800;
static const Uint32 WINDOW_HEIGHT = 600;
static const Uint32 WINDOW_BPP = 32;


int main() {
    using namespace glimac;

    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Unable to initialize SDL" << std::endl;
        return EXIT_FAILURE;
    }

    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if(initted&flags != flags) {
        std::cerr << "Unable to initialize SDL_image" << std::endl;
    }

    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, SDL_OPENGL)) {
        std::cerr << "Unable to open the window and get an OpenGL context" << std::endl;
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption("OpenGL4Imacs", NULL);

    GLenum glewCode = glewInit();
    if(GLEW_OK != glewCode) {
        std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
        return EXIT_FAILURE;
    }

    Program program = loadProgram(
        "./shaders/tex3D.vs.glsl",
        "./shaders/cube.gs.glsl",
        "./shaders/tex3D.fs.glsl"
    );

    FreeflyCamera camera;

    TextureManager manager;
    manager.get("brick.png");

    bool done = false;
    while(!done) {
        Uint32 tStart = SDL_GetTicks();

        // Rendering code goes here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // Application code goes here
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                default:
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_RIGHT) {
                    }
                    break;

                case SDL_QUIT:
                    done = true;
                    break;
            }
        }

        // Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
        SDL_GL_SwapBuffers();

        Uint32 tEnd = SDL_GetTicks();
        Uint32 d = tEnd - tStart;
        if(d < FRAME_DURATION) {
            SDL_Delay(FRAME_DURATION - d);
        }
    }




    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;

}