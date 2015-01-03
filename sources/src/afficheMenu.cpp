#include <iostream>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Cube_obsolete.hpp>
#include <glimac/common.hpp>
#include <glimac/glm.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <cstddef>

#include "Physics.hpp"
#include "Sound.hpp"
#include "Player.hpp"
#include "Timer.hpp"
#include "Menu.hpp"

using namespace glimac;

const GLuint VERTEX_ATTR_POSITION = 3;
const GLuint VERTEX_ATTR_COLOR = 8;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class Vertex2DColor {
    public:
        Vertex2DColor() {
        }
        Vertex2DColor(glm::vec2 pos, glm::vec3 col):position(pos),color(col){
        }
        glm::vec2 position;
        glm::vec3 color;
};

int main(int argc, char** argv) {


// Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "pokeCraft");
    SDL_WarpMouse(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); // set users mouse positioin to the center  

// Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);

    Program program = loadProgram(applicationPath.dirPath() + "shaders/menu.vs.glsl",
                              applicationPath.dirPath() + "shaders/menu.fs.glsl");
    program.use();

    GLuint vbo, vao;

    glBindBuffer (GL_ARRAY_BUFFER, vbo);

    Vertex2DColor vertices1[] = { 
        Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1,0,0)), // premier sommet
        Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0,1,0)), // deuxième sommet
        Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(0,0,1)), // troisième sommet
    
        Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1,0,0)), // premier sommet
        Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(1,0,0)), // deuxième sommet
        Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(0,0,1)) // troisième sommet
    };

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices1, GL_STATIC_DRAW);

    glBindBuffer (GL_ARRAY_BUFFER, 0);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer (GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer( VERTEX_ATTR_POSITION, 2, GL_FLOAT,
                GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) (offsetof(Vertex2DColor, position)));
    glVertexAttribPointer( VERTEX_ATTR_COLOR, 3, GL_FLOAT,
                GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) (offsetof(Vertex2DColor, color)));
    
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true;
            }
            // if(e.type == SDL_MOUSEBUTTONDOWN){
            //     mousePosition = windowManager.getMousePosition();
            // }

            if(e.type == SDL_KEYDOWN)
            {
                SDLKey keyPressed = e.key.keysym.sym;
                Vertex2DColor vertices2[]=
                            { 
                                Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1,0,0)),
                                Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(1,0,0)), 
                                Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(1,0,0)), 

                                Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1,0,0)), 
                                Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(1,0,0)),
                                Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(1,0,0))
                            };
                Vertex2DColor vertices3[] =
                            { 
                                Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(0,1,0)),
                                Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0,1,0)), 
                                Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(0,1,0)), 

                                Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(0,1,0)), 
                                Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(0,1,0)),
                                Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(0,1,0))
                            };
                Vertex2DColor   vertices4[] =
                            { 
                                Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(0,0,1)),
                                Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0,0,1)), 
                                Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(0,0,1)), 

                                Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(0,0,1)), 
                                Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(0,0,1)),
                                Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(0,0,1))
                            };

                switch (keyPressed)
                {
                    case SDLK_p :    // entering the "play" menu: choose player & launch game
                        
                            glBindBuffer (GL_ARRAY_BUFFER, vbo);
                            glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices2, GL_STATIC_DRAW);
                            glBindBuffer (GL_ARRAY_BUFFER, 0);
                        
                        
                        //faire un autre switch pour la selection du player -> fonction (?)
                        // "r" : red player selected -> launch the game
                        // "g" : green player selected -> launch the game
                        // "b" : blue player selected -> launch the game
                        
                        break;


                    case SDLK_s :    // entering the "settings" menu: sound settings
                        
                            glBindBuffer (GL_ARRAY_BUFFER, vbo);
                            glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices3, GL_STATIC_DRAW);
                            glBindBuffer (GL_ARRAY_BUFFER, 0);
                           

                        // "y" : enable sound, "n" : disable sound
                        // "space" : ack tothemain menu

                        break;                      


                    case SDLK_c :    // entering the "commands" menu: commands pictures and explanations
                        
                            glBindBuffer (GL_ARRAY_BUFFER, vbo);
                            glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices4, GL_STATIC_DRAW);
                            glBindBuffer (GL_ARRAY_BUFFER, 0);
                        

                        // "space" : back to the main menu

                        break;


                    case SDLK_q :    // quitting the game
                        done = true;

                        break;


                    default: break;
                }
            }
        }

        /*******************************/
        /******** RENDU A CODER ********/       
        /*******************************/
        
        //nettoie le buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //bind du vao
        glBindVertexArray(vao);
        
        //dessine
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        //debind du vao
        glBindVertexArray(0);
        
        
        /*******************************/
        /******** FIN DU RENDU *********/       
        /*******************************/
        
        windowManager.swapBuffers();
    }
    
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}