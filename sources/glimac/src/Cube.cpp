#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"
#include "glimac/TextureManager.hpp"

namespace glimac {
    Cube::Cube(GLfloat size, Texture texture): size(size), texture(texture) {}
         
    void Cube::setPosition(glm::vec3 position){
        this->position = position;
    }

    glm::vec3 Cube::getPosition(){
        return this->position;
    }


    Texture Cube::getTexture(){ return this->texture;}


    void Cube::display(
        glm::mat4 ProjMatrix,
        FreeflyCamera camera,
        glm::mat4 MVMatrix,
        GLint uMVMatrix,
        GLint uNormalMatrix,
        GLint uMVPMatrix,
        GLint uTexture
    ) {
        MVMatrix = glm::translate(camera.getViewMatrix() * MVMatrix, position); 
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glBindTexture(GL_TEXTURE_2D, texture.getId());

        glDrawArrays(GL_POINTS, 0, 3);
        glUniform1i(uTexture,0);  
    }
}