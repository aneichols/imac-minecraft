#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Map.hpp>
#include <glimac/common.hpp>
#include <glimac/glm.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/TextureManager.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Tree.hpp>
#include <glimac/Skybox.hpp>
#include "glimac/Physics.hpp"
#include "glimac/Player.hpp"
#include "glimac/Timer.hpp"
#include "glimac/Interface.hpp"


using namespace glimac;

const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_NORMAL = 1;
const GLuint VERTEX_ATTR_TEXCOORDS = 2;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FPS = 30;
const float radius = 2.0;
const int nb_cubes = 5;
bool isMenuEnabled = true;
std::string currentTextPath = "assets/textures/brick.png";

struct CubeProgramm {
    Program m_Program;

    GLint uMVPMatrix, uMVMatrix, uNormalMatrix, uTextureCube, uTextureSky, uKd, uKs, uLightDir_vs, uShininess, uLightIntensity, uCameraPos;

    CubeProgramm(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/cube.vs.glsl",
							  applicationPath.dirPath() + "shaders/cube.gs.glsl",
                              applicationPath.dirPath() + "shaders/cube.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTextureCube = glGetUniformLocation(m_Program.getGLId(), "uTextureCube");
        //uTextureSky = glGetUniformLocation(m_Program.getGLId(), "uTextureSky");
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
        uCameraPos = glGetUniformLocation(m_Program.getGLId(), "uCameraPos");
    }
};

struct SkyProgramm {
    Program m_Program;

    GLint uMVPMatrix, uMVMatrix, uNormalMatrix, uTextureSky, uKd, uKs, uLightDir_vs, uShininess, uLightIntensity, uCameraPos;

    SkyProgramm(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/sky.vs.glsl",
                              applicationPath.dirPath() + "shaders/sky.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTextureSky = glGetUniformLocation(m_Program.getGLId(), "uTextureSky");
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
        uCameraPos = glGetUniformLocation(m_Program.getGLId(), "uCameraPos");
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

	// TODO always keep the mouse inside the window
}

void controlGame(   SDLWindowManager &windowManager,
                    Player &player,
                    glm::ivec2 &mousePosition,
                    Map &map,
                    TextureManager &textureManager,
                    int &currentTexture,
                    std:: string texturesPaths[]
                    ){
    
    glm::ivec2 mousePosition_actual = windowManager.getMousePosition();
    glm::ivec2 offset = windowManager.getMousePosition() - mousePosition;
    player.rotateUp(-offset.y);
    player.rotateLeft(-offset.x);
    mousePosition = mousePosition_actual;
    player.updateAlt(0.1);

    float move = 1;
    
    if(windowManager.isKeyPressed(SDLK_z)){
       player.moveFront(move);
    }

    if(windowManager.isKeyPressed(SDLK_s)){
       player.moveFront(-move);
    }

    if(windowManager.isKeyPressed(SDLK_q)){
       player.moveLeft(move);
    }

    if(windowManager.isKeyPressed(SDLK_d)){
       player.moveLeft(-move);
    }

    if(windowManager.isKeyPressed(SDLK_SPACE)){
       player.jump(move);
    }

    if(windowManager.isKeyPressed(SDLK_UP) || windowManager.isKeyPressed(SDLK_DOWN)){
       currentTexture = (++ currentTexture) % 4;
    }

    if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
        map.addCube(glm::ivec3((player.camera.getFrontVector() * radius) + player.camera.getPosition()), textureManager.get(texturesPaths[currentTexture]));
        player.buildCube();

    }

    if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)){
        if(map.destroyCube(glm::ivec3((player.camera.getFrontVector() * radius) + player.camera.getPosition()))) player.destroyCube();

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
    * TIMER
    *********************************/
	Pokecraft::Timer timer(FPS);


    /*********************************
    * VBO, VAO
    *********************************/
    GLuint vbo, vao;
    glGenBuffers (1, &vbo);
    glGenVertexArrays(1, &vao);


    /*********************************
    * Objects we need
    *********************************/

    //FreeflyCamera camera;
    Player player(glm::vec3 (0,6,0));
    TextureManager textureManager;
    Map map(textureManager);
    //Tree tree(glm::ivec3(0,0,0), textureManager);   

    Sphere skySphere(50.f, 32, 16);
    Texture skyTexture = Texture::load("assets/textures/sky.jpg");
    Skybox skybox(glm::vec3(0.f,0.f,0.f), skySphere, skyTexture);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        skybox.load();
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(vao);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
            glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /*********************************
    * SHADERS
    *********************************/

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    CubeProgramm cubeProgramm(applicationPath);
    SkyProgramm skyProgramm(applicationPath);
     // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glDepthFunc(GL_LESS);
    // Accept fragment if it closer to the camera than the former one



    /*********************************
    * TEXTURES
    *********************************/
    int currentTexture = 0;

    std::string texturesPaths[] = {
        "assets/textures/brick.png",
        "assets/textures/herbe.jpg",
        "assets/textures/rock.png",
        "assets/textures/sand.jpg"
    };

    /*********************************
    * MATERIAU
    *********************************/

    glm::vec3 Kd, Ks;
    float shininess;

    Kd = glm::vec3(1.f, 1.f, 1.f); // replace by texture ! oh yeah
    Ks = glm::vec3(0.f, 0.f, 0.f);
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
   

    /*mouse position : default is windows center */
    glm::ivec2 mousePosition = glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

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
            player.getSoundPlayer().play(Pokecraft::BACKGROUND);
            isMenuEnabled = false;
        }
        else{
        	controlGame(windowManager, player, mousePosition, map, textureManager , currentTexture, texturesPaths);
        }

        /*********************************
         * RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBindVertexArray(vao);

        projMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.f);
        MVMatrix = glm::mat4(1);

        //glBindVertexArray(vao);
        cubeProgramm.m_Program.use();


        glUniform3fv(cubeProgramm.uKs, 1, glm::value_ptr(Ks));
        glUniform3fv(cubeProgramm.uKd, 1, glm::value_ptr(Kd)); // no need anymore
        glUniform3fv(cubeProgramm.uCameraPos, 1, glm::value_ptr(player.camera.getViewMatrix()));
        glUniform1f(cubeProgramm.uShininess, 50);

        glUniform3f(cubeProgramm.uLightIntensity, 0.4, 0.6, 0.6);

        glm::vec3 position_worldspace(1, 1, 1);
        glm::vec3 position_viewspace = glm::vec3(MVMatrix * glm::vec4(position_worldspace, 0));
        glUniform3fv(cubeProgramm.uLightDir_vs, 1, glm::value_ptr(position_viewspace));

        //map or some very beautiful landscape
        map.display(projMatrix, 
                    player, 
                    MVMatrix, 
                    cubeProgramm.uMVMatrix, 
                    cubeProgramm.uNormalMatrix, 
                    cubeProgramm.uMVPMatrix, 
                    cubeProgramm.uTextureCube,
                    textureManager
                    );
        //glBindVertexArray(0);

    /*********************************
    * Tree
    *********************************/

    /*tree.display(projMatrix, 
                    player, 
                    MVMatrix, 
                    cubeProgramm.uMVMatrix, 
                    cubeProgramm.uNormalMatrix, 
                    cubeProgramm.uMVPMatrix, 
                    cubeProgramm.uTextureCube,
                    textureManager);*/


        
        glUseProgram(0);
        skyProgramm.m_Program.use();


         glBindVertexArray(vao);
        //Very beautiful sky
        skybox.setPosition(player.camera.getPosition());
        skybox.display( projMatrix,
                        player.camera.getViewMatrix() * MVMatrix,
                        SDL_GetTicks(), 
                        skyProgramm.uMVMatrix, 
                        skyProgramm.uNormalMatrix, 
                        skyProgramm.uMVPMatrix,
                        skyProgramm.uTextureSky);
        glUseProgram(0);
        glBindVertexArray(0);



    /*********************************
    * Mini Map
    *********************************/
    glLoadIdentity();
    glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

    DrawImage(WINDOW_WIDTH - 100 - 20 - 7.5 + (player.getPosition().x / 4),
            63 - 7.5 + (player.getPosition().z / 4),
            15,
            15,
            "assets/textures/head4.png");


    DrawImage(WINDOW_WIDTH - 200 - 20, 20, 200, 96, "assets/textures/hoenn.png");
    

    /*********************************
    * Current Texture
    *********************************/
    
    glLoadIdentity();
    glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    //DrawImage(WINDOW_WIDTH - 200 - 20, 20, 200, 96, "assets/textures/hoenn.png");

    DrawImage(WINDOW_WIDTH - 300, 50, 50, 50, texturesPaths[currentTexture].c_str());

        windowManager.swapBuffers();

		timer.sleepUntilNextTick();
    }


    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    textureManager.deleteTexture();

    return EXIT_SUCCESS;
}
