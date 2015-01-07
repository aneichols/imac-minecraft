#pragma once 
#include <opencv2/opencv.hpp>
#include <vector>
#include "FreeflyCamera.hpp"
#include "common.hpp"
#include "Cube.hpp"
#include "Player.hpp"
#include "Tree.hpp"
#include <glimac/glm.hpp>
#include <glimac/TextureManager.hpp>




namespace glimac {

	class Map{
	private:

		std::vector<CubeAtom> destructibleCube;
		std::vector<CubeAtom> undestructibleCube;

		void buildLevel(std::string path, TextureManager& textureManager, unsigned int levelNumber);
		void buildMap(TextureManager& textureManager);

	public:
		Map(TextureManager& textureManager) {
			buildMap(textureManager);
		}
		
		void addCube(glm::ivec3 position, const Texture &text);
		bool destroyCube(glm::ivec3 position);


		void display(
            glm::mat4 ProjMatrix,
            Player& player,
            glm::mat4 MVMatrix,
            GLint uMVMatrix,
            GLint uNormalMatrix,
            GLint uMVPMatrix,
            GLint uTexture,
            TextureManager& textureManager
        );
	};

}