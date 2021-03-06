#pragma once
#include "glimac/Sound.hpp"
#include <glimac/FreeflyCamera.hpp>

namespace glimac {

	enum State {Jumping, Falling, Walking, unMoving}; //  0 1 2

	class Player {
		void build(glm::vec3 position);

	public:
      Player(glm::vec3 position) {
          build(position);
      }

      State state = unMoving;
	  FreeflyCamera camera;

	  const FreeflyCamera& getCamera() const;
	  glm::vec3 getPosition();
	  void setPosition(glm::vec3 position);

	  void moveFront(float t);
	  void moveLeft(float t);
  	  void rotateLeft(float degrees);
	  void rotateUp(float degrees);
	  void jump(float t);
	  void buildCube();
	  void destroyCube();
	  void updateAlt(float t);
	  Pokecraft::Sound& getSoundPlayer(){  return soundPlayer;}
	  void gravity(bool down = true);
	  int getWidth() const;
	  int getHeight() const;

	private:
		glm::vec3 position;
		Pokecraft::Sound soundPlayer;
		float threshold;
		float alt;
		int width = 1, height = 3;
	};
}