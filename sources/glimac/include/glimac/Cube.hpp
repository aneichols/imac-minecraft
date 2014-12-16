#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include "common.hpp"
#include <glimac/Program.hpp>

namespace glimac {

// Représente un Cube.
    class Cube {

        // Alloue et construit les données (implantation dans le .cpp)
        void build(GLfloat size);

        public:
            // Constructeur: vbo + ibo.
            Cube(GLfloat size):
                m_nVertexCount(0) {
                build(size); 
            }

            // Renvoie le pointeur vers les données
            const ShapeVertex* getDataPointer() const {
                return &m_Vertices[0];
            }
            
            // Renvoie le nombre de vertex
            GLsizei getVertexCount() const {
                return 36;
            }
            
        private:
            GLuint vbo, vao, ibo;
            std::vector<ShapeVertex> m_Vertices;
            GLsizei m_nVertexCount; // Nombre de sommets
    };
}