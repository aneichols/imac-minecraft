#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

namespace glimac {


    void Cube::build(GLfloat s) {
        ShapeVertex vertex;
        //tableau de positions

/*
                    -1.0, -1.0, -1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1
                    -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1

                    1.0, -1.0, 1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,       // Face 2
                    1.0, -1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 2

                    -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, -1.0, -1.0,      // Face 3
                    -1.0, -1.0, 1.0,   -1.0, -1.0, -1.0,   1.0, -1.0, -1.0,    // Face 3

                    -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4
                    -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4

                    -1.0, -1.0, -1.0,   -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,     // Face 5
                    -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   -1.0, 1.0, 1.0,     // Face 5

                    -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 6
                    -1.0, 1.0, 1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0}
*/
        glm::vec3 pos[] = {
            glm::vec3(-1.0, -1.0, -1.0),   glm::vec3(1.0, -1.0, -1.0),   glm::vec3(1.0, 1.0, -1.0),     // Face 1
            glm::vec3(-1.0, -1.0, -1.0),   glm::vec3(-1.0, 1.0, -1.0),   glm::vec3(1.0, 1.0, -1.0),     // Face 1

            glm::vec3(1.0, -1.0, 1.0),   glm::vec3(1.0, -1.0, -1.0),   glm::vec3(1.0, 1.0, -1.0),       // Face 2
            glm::vec3(1.0, -1.0, 1.0),   glm::vec3(1.0, 1.0, 1.0),   glm::vec3(1.0, 1.0, -1.0),         // Face 2

            glm::vec3(-1.0, -1.0, 1.0),   glm::vec3(1.0, -1.0, 1.0),   glm::vec3(1.0, -1.0, -1.0),      // Face 3
            glm::vec3(-1.0, -1.0, 1.0),   glm::vec3(-1.0, -1.0, -1.0),   glm::vec3(1.0, -1.0, -1.0),    // Face 3

            glm::vec3(-1.0, -1.0, 1.0),   glm::vec3(1.0, -1.0, 1.0),   glm::vec3(1.0, 1.0, 1.0),        // Face 4
            glm::vec3(-1.0, -1.0, 1.0),   glm::vec3(-1.0, 1.0, 1.0),   glm::vec3(1.0, 1.0, 1.0)        // Face 4

            glm::vec3(-1.0, -1.0, -1.0),   glm::vec3(-1.0, -1.0, 1.0),   glm::vec3(-1.0, 1.0, 1.0),     // Face 5
            glm::vec3(-1.0, -1.0, -1.0),   glm::vec3(-1.0, 1.0, -1.0),   glm::vec3(-1.0, 1.0, 1.0),     // Face 5

            glm::vec3(-1.0, 1.0, 1.0),   glm::vec3(1.0, 1.0, 1.0),   glm::vec3(1.0, 1.0, -1.0),         // Face 6
            glm::vec3(-1.0, 1.0, 1.0),   glm::vec3(-1.0, 1.0, -1.0),   glm::vec3(1.0, 1.0, -1.0),



        };      // Face 6

        glm::vec3 normals[] = {
            glm::vec3(1.0, 0.0, 1.0),
            glm::vec3(1.0, 0.0, 0.0),
            glm::vec3(0.0, 1.0, 0.0),
            glm::vec3(0.0, 0.0, 1.0),
            glm::vec3(1.0, 0.0, 0.0),
            glm::vec3(0.0, 1.0, 0.0)
        };

        vertex.texCoords = glm::vec2(0,0);

        for (int i = 0; i < 36; i++){
            vertex.position = pos[i];
            int j = i / 6;
            std::cout << j << std::endl;
            vertex.normal = normals[j];
            m_Vertices.push_back(vertex);
        }
    }
}