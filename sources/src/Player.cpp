#include <iostream>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include "Player.hpp"
#include <glimac/FreeflyCamera.hpp>

//TODO camera

namespace glimac {

	void Player::build(glm::vec3 position) {
		this->position = position;
		std::cout << "player builded" << std::endl;
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

	void Player::jump(float degrees){
		if (state == Jumping || state == Falling) return;
	}

	void Player::display(){
		std::cout << "displaying player OH YEAH" << std::endl;
	}
}