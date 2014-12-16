#pragma once

namespace glimac {

class FreeflyCamera {

   void build();
   
    public:
        FreeflyCamera(){
             build();
        }

        void moveLeft(float t);
        void moveFront(float t);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        glm::mat4 getViewMatrix() const;

    private:
        glm::vec3 m_position;
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;
        float m_fPhi;
        float m_fTheta;
        void computeDirectionVectors();

    };
}