#include <iostream>
#include <math.h> 
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include "glimac/Player.hpp"
#include "glimac/Sound.hpp"
#include <glimac/FreeflyCamera.hpp>

namespace glimac {

	void Player::build(glm::vec3 position) {

		this->position = position;
		this->camera.setPosition(position);
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

	void Player::gravity(bool down) {
		State tmp = state;
		state = Falling;

		updateAlt(down ? 1 : -1);

		state = tmp;
	}

	const FreeflyCamera& Player::getCamera() const {
		return camera;
	}

	glm::vec3 Player::getPosition() {
		return camera.getPosition();
	}

	void Player::setPosition(glm::vec3 position) {
		build(position);
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

	void Player::buildCube(){
		soundPlayer.play(Pokecraft::BUILD);
	}

	void Player::destroyCube(){
		soundPlayer.play(Pokecraft::DESTROY);
	}

	void Player::rotateLeft(float degrees){
		camera.rotateLeft(degrees);
	}

	void Player::jump(float t){
		if (state == Jumping || state == Falling) return;
		soundPlayer.play(Pokecraft::JUMP);
		state = Jumping;
	}

	int Player::getWidth() const {
		return width;
	}

	int Player::getHeight() const {
		return height;
	}
}