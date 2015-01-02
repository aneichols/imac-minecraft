#include <iostream>
#include <math.h> 
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include "glimac/Player.hpp"
#include <glimac/FreeflyCamera.hpp>

//TODO camera

namespace glimac {

	void Player::build(glm::vec3 position) {
		this->position = position;
		this->camera.setPosition(position);
		std::cout << "player builded" << std::endl;
		alt = 0.f;
		threshold = 1.5f;
	}

	void Player::updateAlt(float t){
		if(state != Jumping && state != Falling) return;

		if(state == Jumping){
			if(0 >= (threshold - alt)){
				state = Falling;
			}else{
				alt += t;
				camera.moveUp(0.1 * cos(t));
			}
		}

		if(state == Falling){
			alt -= t;
			camera.moveUp(0.1 * -cos(t));
			if(alt <= 0){
				state = unMoving;
			}
		}
	}

	const FreeflyCamera& Player::getCamera() const {
		return camera;
	}

	glm::vec3 Player::getPosition() {
		return camera.getPosition();
	}

	void Player::moveFront(float t){
		camera.moveFront(t);
	}

	void Player::moveLeft(float t){
		camera.moveLeft(t);
	}

	void Player::rotateUp(float t){
		camera.rotateUp(t);
	}

	void Player::rotateLeft(float degrees){
		camera.rotateLeft(degrees);
	}

	void Player::jump(float t){
		if (state == Jumping || state == Falling) return;
		state = Jumping;
	}

	void Player::display(){
		std::cout << "displaying player OH YEAH" << std::endl;
	}

}