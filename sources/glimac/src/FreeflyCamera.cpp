#include <iostream>
#include <glimac/glm.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <math.h>

namespace glimac {

	void FreeflyCamera::build() {
		m_position = glm::vec3(0.f, 0.f, 0.f);
    m_fPhi = M_PI;
    m_fTheta = 0.f;
    computeDirectionVectors();
  }

  void FreeflyCamera::computeDirectionVectors(){
	   	m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), 
	   														sin(m_fTheta), 
	   														cos(m_fTheta) * cos(m_fPhi)
	   														);
	   	//L
	   	m_LeftVector = glm::vec3(sin (m_fPhi + M_PI/2.f), 0.f , cos(m_fPhi + M_PI/2.f));
	   	//U
	   	m_UpVector = glm::cross (m_FrontVector, m_LeftVector);
  }

   void FreeflyCamera::moveLeft(float t){
   		m_position += t * m_LeftVector;
   }

   void FreeflyCamera::moveFront(float t){
   		m_position += t * m_FrontVector;
   }

  void FreeflyCamera::rotateLeft(float degrees){
		m_fPhi += glm::radians(degrees);
		computeDirectionVectors();
	}

	void FreeflyCamera::rotateUp(float degrees){
		m_fTheta += glm::radians(degrees);
		computeDirectionVectors();
	}

  glm::mat4 FreeflyCamera::getViewMatrix() const {

  	glm::mat4 viewMatrix = glm::mat4 (1.0);
  	viewMatrix = glm::lookAt(m_position, m_position + m_FrontVector,  glm::cross (m_FrontVector, m_LeftVector));
		return viewMatrix ;
	}
}