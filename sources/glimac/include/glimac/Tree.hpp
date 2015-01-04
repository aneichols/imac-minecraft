#pragma once 
#include <opencv2/opencv.hpp>
#include <vector>
#include "FreeflyCamera.hpp"
#include "common.hpp"
#include "Cube.hpp"
#include "Player.hpp"
#include <glimac/glm.hpp>
#include <glimac/TextureManager.hpp>


namespace glimac {

	class Tree{
	private:

		std::vector<CubeAtom> destructibleCube;
		glm::vec3 position;

		void buildTree(TextureManager& textureManager);
		void buildTrees(std::string path, TextureManager& textureManager);
		

	public:
		std::vector<CubeAtom> getAllTreeCubes();
		Tree(glm::vec3 position, TextureManager& textureManager) : position(position) {
			buildTree(textureManager);
		}
		
		void addCube(glm::vec3 position, const Texture &text);
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