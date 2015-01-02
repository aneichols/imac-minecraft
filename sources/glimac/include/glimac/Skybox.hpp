#pragma once

#include <string>
#include "Sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.hpp"
#include <SDL/SDL.h>

namespace glimac {

    class Skybox {

        Sphere shape;
        glm::vec3 position;
        Uint32 tStart;
        Texture texture;

        public:
            void load();
            Skybox(glm::vec3 position, Sphere shape, Texture texture) : position(position), shape(shape), texture(texture) {}
            void setPosition(glm::vec3 pos);
            void display(glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Uint32 tStart, GLint uMVMatrix, GLint uNormalMatrix, GLint uMVPMatrix, GLint uTexture);
    };
    
}

/*
#include <string>
#include "Sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.hpp"
#include "glimac/FreeflyCamera.hpp"






namespace glimac {

    class Skybox {

        Sphere skySphere;
        glm::vec3 position;
        Texture texture;

        public:
            void load();
            Skybox(glm::vec3 position, Sphere skySphere, Texture texture) : position(position), skySphere(skySphere), texture(texture) {}
            void setPosition(glm::vec3 pos);
            void display(        glm::mat4 ProjMatrix,
        FreeflyCamera camera,
        glm::mat4 MVMatrix,
        GLint uMVMatrix,
        GLint uNormalMatrix,
        GLint uMVPMatrix,
        GLint uTexture);
    };
    
}*/