#include <iostream>
#include <glimac/glm.hpp>
#include <glimac/TrackballCamera.hpp>

namespace glimac {

	void TrackballCamera::build(float m_fDistance, float m_fAngleXt, float m_fAngleY) {
		m_fDistance = 5.0;
		m_fAngleX = 0;
    m_fAngleY = 0;
  }

  float TrackballCamera::getDistance() const {return m_fDistance;}
	float TrackballCamera::getAngleX() const {return m_fAngleX; }
	float TrackballCamera::getAngleY()const { return m_fAngleY; }

	float TrackballCamera::setDistance(float dist){m_fDistance = dist ;}
	float TrackballCamera::setAngleX(float angleX){m_fAngleX = angleX; }
	float TrackballCamera::setAngleY(float angleY){m_fAngleY = angleY;}

// permettant d'avancer / reculer la caméra. Lorsque delta est positif la caméra doit avancer, sinon elle doit reculer.
void TrackballCamera::moveFront(float delta){
	m_fDistance += delta;
}
// permettant de tourner latéralement autour du centre de vision.
void TrackballCamera::rotateLeft(float degrees){
	m_fAngleX += degrees;
}
// permettant de tourner verticalement autour du centre de vision.
void TrackballCamera::rotateUp(float degrees){
	m_fAngleY += degrees;
}

glm::mat4 TrackballCamera::getViewMatrix() const {
	  float ax = glm::radians(m_fAngleX);
	  float ay = glm::radians(m_fAngleY);

	glm::mat4 viewMatrix = glm::mat4 (1.0);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, -getDistance()));
	viewMatrix = glm::rotate (viewMatrix, ax, glm::vec3(1,0,0));
	viewMatrix = glm::rotate (viewMatrix, ay, glm::vec3(0,1,0));
	
	return viewMatrix;
	}


}

