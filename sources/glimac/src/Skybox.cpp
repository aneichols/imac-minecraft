#include "glimac/Skybox.hpp"

namespace glimac {

    void Skybox::setPosition(glm::vec3 pos) {
        position = pos;
    }

    void Skybox::load() {
        glBufferData(GL_ARRAY_BUFFER, shape.getVertexCount() * sizeof(ShapeVertex), shape.getDataPointer(), GL_STATIC_DRAW);
    }

    void Skybox::display(glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Uint32 tStart, GLint uMVMatrix, GLint uNormalMatrix, GLint uMVPMatrix, GLint uTexture) {
        float revolutionSpeed = (float)tStart / 4000;
        MVMatrix = glm::translate(MVMatrix, position); 
        MVMatrix = glm::rotate(MVMatrix, revolutionSpeed, glm::vec3(0, 1, 0));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

        glBindTexture(GL_TEXTURE_2D, texture.getId());
        glDrawArrays(GL_TRIANGLES, 0, shape.getVertexCount());
        glUniform1i(uTexture,0);

    }
}


/*


#include "glimac/Skybox.hpp"
#include <iostream>

namespace glimac {

	void Skybox::setPosition(glm::vec3 pos) {
		position = pos;
	}

	void Skybox::load() {
       glBufferData(GL_ARRAY_BUFFER, skySphere.getVertexCount() * sizeof(ShapeVertex), skySphere.getDataPointer(), GL_STATIC_DRAW);
	}

    void Skybox::display(        glm::mat4 ProjMatrix,
        FreeflyCamera camera,
        glm::mat4 MVMatrix,
        GLint uMVMatrix,
        GLint uNormalMatrix,
        GLint uMVPMatrix,
        GLint uTexture) {
       
        MVMatrix = glm::translate(camera.getViewMatrix() * MVMatrix, position);  
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

        glBindTexture(GL_TEXTURE_2D, texture.getId());
        glDrawArrays(GL_TRIANGLES, 0, skySphere.getVertexCount());
        glUniform1i(uTexture,0);

    }
}

*/