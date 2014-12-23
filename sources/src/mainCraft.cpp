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
#include "Physics.hpp"
#include "Sound.hpp"

using namespace glimac;

const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_NORMAL = 1;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int nb_cubes = 5;
bool isMenuEnabled = true;
bool isSoundEnabled = true;

struct CubeProgramm {
    Program m_Program;

    GLint uMVPMatrix, uMVMatrix, uNormalMatrix, uEarthTexture, uCloudTexture, uKd, uKs, uLightPos_vs, uShininess, uLightIntensity;

    CubeProgramm(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/allShaders.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightPos_vs = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }
};

/****************************************************************************************
* Should these functions be in separated file ? menuControler and gameControler ?
 ****************************************************************************************/

void controlMenu(SDLWindowManager &windowManager, glm::ivec2 &mousePosition){
    std::cout << "menu" << std::endl;
    isMenuEnabled = false;

    /* reset mouse position if user choose to launch the game */
    SDL_WarpMouse(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    mousePosition = glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void controlGame(SDLWindowManager &windowManager, FreeflyCamera &camera, glm::ivec2 &mousePosition, Sound &soundPlayer){

    glm::ivec2 mousePosition_actual = windowManager.getMousePosition();
    glm::ivec2 offset = windowManager.getMousePosition() - mousePosition;
    camera.rotateUp(-offset.y);
    camera.rotateLeft(-offset.x);
    mousePosition = mousePosition_actual;

/*
*   TODO : bug chiant : si on fait un tour complet sur soi, la cémara devient folle !
*/

    if(windowManager.isKeyPressed(SDLK_z)){
        camera.moveFront(0.001);
     }

    if(windowManager.isKeyPressed(SDLK_s)){
        camera.moveFront(-0.001);
     }

    if(windowManager.isKeyPressed(SDLK_q)){
        camera.moveLeft(0.001);
     }


    if(windowManager.isKeyPressed(SDLK_d)){
        camera.moveLeft(-0.001);
     }

    if(windowManager.isKeyPressed(SDLK_SPACE)){
        soundPlayer.play(Jump);
     }

        if(windowManager.isKeyPressed(SDLK_SPACE)){
        soundPlayer.play(Jump);
     }
}

/****************************************************************************************
 ****************************************************************************************/

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

    /*********************************
    * SOUNDS
    *********************************/
     //Initialize SDL_mixer
    Sound soundPlayer;



    /*********************************
    * Objects we need
    *********************************/

    FreeflyCamera camera;
    Cube cube(1);

    /*********************************
    * SHADERS
    *********************************/

    glEnable(GL_DEPTH_TEST);
    CubeProgramm cubeProgramm(applicationPath);
    glEnable(GL_DEPTH_TEST);
     // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glDepthFunc(GL_LESS);
    // Accept fragment if it closer to the camera than the former one



    /*********************************
    * TEXTURES
    *********************************/

    /*********************************
    * UNIFORM VAR
    *********************************/

    /*********************************
    * CAMERA INITIALIZATION
    *********************************/

    /*********************************
    * MATERIAU
    *********************************/

    glm::vec3 Kd, Ks;
    float shininess;

    Kd = glm::vec3(1.f, 1.f, 1.f);
    Ks = glm::vec3(1.f, 1.f, 1.f);
    shininess = 1.f;

    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;
    glm::mat4 projMatrix = glm::perspective(
                                glm::radians(70.f),
                                (float) (WINDOW_WIDTH / WINDOW_HEIGHT),
                                0.1f,
                                100.f
                            );


    /*********************************
     * INITIALIZATION CODE
     *********************************/

    GLuint vbo, vao;
    glGenBuffers (1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount() * sizeof(ShapeVertex),cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *) offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *) offsetof(ShapeVertex, normal));


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /*mouse position : default is windows center */
    glm::ivec2 mousePosition = glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);


    //testing sounds
    soundPlayer.play(Background);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true;
            }

            if(e.type == SDL_MOUSEBUTTONDOWN){
                mousePosition = windowManager.getMousePosition();
            }
        }

        /**************************************
        *               EVENTS
        *
        *   ___ game states ____
        *
        *   1. menu enabled : display the menu
        *   2. game enabled : dispay the game
        *
        *    use isMenuEnabled
        *
         **************************************/

        if(isMenuEnabled){
            controlMenu(windowManager, mousePosition);
        }
        else{

            controlGame(windowManager, camera, mousePosition, soundPlayer);
        }

        /*********************************
         * RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);

        projMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.f);
        MVMatrix = camera.getViewMatrix();

        glBindVertexArray(vao);
        cubeProgramm.m_Program.use();


        glUniform3fv(cubeProgramm.uKs, 1, glm::value_ptr(Ks));
        glUniform3fv(cubeProgramm.uKd, 1, glm::value_ptr(Kd));
        glUniform1f(cubeProgramm.uShininess, 1);

        glUniform3f(cubeProgramm.uLightIntensity, 10, 10, 10);

        glm::vec3 position_worldspace(1, 1, 1);
        glm::vec3 position_viewspace = glm::vec3(MVMatrix * glm::vec4(position_worldspace, 1));
        glUniform3fv(cubeProgramm.uLightPos_vs, 1, glm::value_ptr(position_viewspace));

        //map or some very beautiful landscape 
        for(int i = 0; i < nb_cubes; i++){
            glm::mat4 cubeMVMatrix = MVMatrix;
            cubeMVMatrix = glm::translate(cubeMVMatrix, glm::vec3( 0, 0 , -3.f)); 
            glUniformMatrix4fv(cubeProgramm.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * cubeMVMatrix));
            glUniformMatrix4fv(cubeProgramm.uMVMatrix, 1, GL_FALSE, glm::value_ptr(cubeMVMatrix));
            glUniformMatrix4fv(cubeProgramm.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(cubeMVMatrix))));
            glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
        }
        glBindVertexArray(0);
        windowManager.swapBuffers();
    }

    //FIX ME !
    soundPlayer.clean();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}