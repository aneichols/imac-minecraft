
#include <glimac/glm.hpp>
#include "glimac/FreeflyCamera.hpp"

namespace glimac {

  static float degrees_to_radians(float degrees) {
    float pi = glm::pi<float>();
    return pi * degrees / 180.f;
  }

  void FreeflyCamera::computeDirectionVectors() {
    float PI = glm::pi<float>();

    float cosphi = glm::cos(m_fPhi), sinphi = glm::sin(m_fPhi);
    float costheta = glm::cos(m_fTheta), sintheta = glm::sin(m_fTheta);

    m_FrontVector = glm::vec3(
      costheta * sinphi,
      sintheta,
      costheta * cosphi
    );

    m_LeftVector = glm::vec3(
      glm::sin(m_fPhi + PI/2.),
      0,
      glm::cos(m_fPhi + PI/2.)
    );

    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
  }

  FreeflyCamera::FreeflyCamera() {
    m_fPhi = glm::pi<float>();
    m_fTheta = 0;

    computeDirectionVectors();
  }

  void FreeflyCamera::moveLeft(float t) {
    m_Position += t * m_LeftVector;
  }

  void FreeflyCamera::moveFront(float t) {
    m_Position[0] += t * m_FrontVector[0];
    m_Position[2] += t * m_FrontVector[2];
  }

  void FreeflyCamera::moveUp(float t) {
    m_Position += t * m_UpVector;
  }

  void FreeflyCamera::setPosition(glm::vec3 position){
    m_Position = position;
  }

  glm::vec3 FreeflyCamera::getPosition(){
    return m_Position;
  }

  void FreeflyCamera::rotateLeft(float degrees) {
    float radians = degrees_to_radians(degrees);
    m_fPhi += radians;

    computeDirectionVectors();
  }

  void FreeflyCamera::rotateUp(float degrees) {
    if (m_fTheta + degrees_to_radians(degrees) > 1.f || m_fTheta + degrees_to_radians(degrees) < -1.f) return;
    float radians = degrees_to_radians(degrees);
    m_fTheta += radians;
    computeDirectionVectors();
  }

  glm::mat4 FreeflyCamera::getViewMatrix() const {
    return glm::lookAt(
      m_Position,
      m_Position + m_FrontVector,
      m_UpVector
    );
  }

}
