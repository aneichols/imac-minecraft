#pragma once
#include "glimac/Sound.hpp"
#include <glimac/FreeflyCamera.hpp>

namespace glimac {

	enum State {Jumping, Falling, Walking, unMoving}; //  0 1 2

	class Player {
		void build(glm::vec3 position, Pokecraft::Sound &soundPlayer);

	public:
      Player(glm::vec3 position, Pokecraft::Sound &soundPlayer) {
          build(position, soundPlayer);
      }

      State state = unMoving;
	  FreeflyCamera camera;

	  const FreeflyCamera& getCamera() const;
	  glm::vec3 getPosition();

	  void moveFront(float t);
	  void moveLeft(float t);
  	  void rotateLeft(float degrees);
	  void rotateUp(float degrees);
	  void jump(float t);
	  void buildCube();
	  void destroyCube();
	  void display();
	  void updateAlt(float t);

	private:
		glm::vec3 position;
		Pokecraft::Sound soundPlayer;
		float threshold;
		float alt;
	};
}