#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

#include "common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include "glimac/Program.hpp"
#include "glimac/Texture.hpp"

namespace glimac {

    class Cube {

    private:
        GLfloat size = 1;
        glm::vec3 position = glm::vec3(1, 1, 1);
        Texture texture;

        // Alloue et construit les données (implantation dans le .cpp)
        void build(GLfloat size, Texture texture);

     public:
         Cube(GLfloat size, Texture texture);
         void setPosition(glm::vec3 position);
         glm::vec3 getPosition();
         Texture getTexture();
         void display(
            glm::mat4 ProjMatrix,
            FreeflyCamera camera,
            glm::mat4 MVMatrix,
            GLint uMVMatrix,
            GLint uNormalMatrix,
            GLint uMVPMatrix,
            GLint uTexture,
            GLint uSize
        );
    };
}