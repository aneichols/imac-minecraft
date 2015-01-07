
#ifndef H_FREEFLYCAMERA
#define H_FREEFLYCAMERA

#include <glimac/glm.hpp>

namespace glimac {

  class FreeflyCamera {

    glm::vec3 m_Position;
    float m_fPhi, m_fTheta;
    glm::vec3 m_FrontVector, m_LeftVector, m_UpVector;
    void computeDirectionVectors();

  public:

    FreeflyCamera();

    void moveLeft(float t);
    void moveFront(float t);
    void moveUp(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    glm::vec3  getFrontVector();

    glm::mat4 getViewMatrix() const;

  };

}

#endif
