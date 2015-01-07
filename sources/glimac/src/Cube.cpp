#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"
#include "glimac/TextureManager.hpp"

namespace glimac {

    void Cube::display(
        glm::vec3 position,
        GLuint tex_id,
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
        glBindTexture(GL_TEXTURE_2D, tex_id);

        glDrawArrays(GL_POINTS, 0, 3);
        glUniform1i(uTexture,0);  
    }
}