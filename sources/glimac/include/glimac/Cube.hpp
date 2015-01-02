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

     public:

        static void display(
            glm::vec3 position,
            GLuint tex_id,
            glm::mat4 ProjMatrix,
            FreeflyCamera camera,
            glm::mat4 MVMatrix,
            GLint uMVMatrix,
            GLint uNormalMatrix,
            GLint uMVPMatrix,
            GLint uTexture
        );
    };
}