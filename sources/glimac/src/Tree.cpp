#include "glimac/Tree.hpp"
#include <cmath>

namespace glimac {

	void Tree::buildTree(TextureManager& textureManager){
		CubeAtom cubeAtom;
		const Texture& texture1 = textureManager.get("assets/textures/wood.jpg");
		const Texture& texture2 = textureManager.get("assets/textures/leaves.jpg");

		//tronc
		cubeAtom.position = position + glm::vec3( 0, 4, 0);
		cubeAtom.tex_id = texture1.getId();

		destructibleCube.push_back(cubeAtom);

		cubeAtom.position =position + glm::vec3( 0, 5, 0);
		cubeAtom.tex_id = texture1.getId();

		destructibleCube.push_back(cubeAtom);

				cubeAtom.position =position + glm::vec3( 0, 3, 0);
		cubeAtom.tex_id = texture1.getId();

		destructibleCube.push_back(cubeAtom);

				cubeAtom.position =position + glm::vec3( 0, 2, 0);
		cubeAtom.tex_id = texture1.getId();

		destructibleCube.push_back(cubeAtom);

		//leaves
			for( int i= 5 ; i<= 7; i++){
				/*1*/cubeAtom.position = position +glm::vec3( 0, i, 0);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);

				/*2*/cubeAtom.position = position +glm::vec3( 1, i, 0);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);

				/*3*/cubeAtom.position = position +glm::vec3( -1, i, 0);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);

				/*4*/cubeAtom.position = position +glm::vec3( 0, i, 1);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);

				/*5*/cubeAtom.position = position +glm::vec3( 0, i, -1);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);

				/*6*/cubeAtom.position = position +glm::vec3( 1, i, 1);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);

				/*7*/cubeAtom.position = position +glm::vec3( 1, i, -1);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);

				/*8*/cubeAtom.position =position + glm::vec3( -1, i, 1);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);

				/*9*/cubeAtom.position = position +glm::vec3( -1, i, -1);
				cubeAtom.tex_id = texture2.getId();

				destructibleCube.push_back(cubeAtom);
			}

	}

	std::vector<CubeAtom> Tree::getAllTreeCubes(){

		return destructibleCube;
	}


	void Tree::display(
            glm::mat4 ProjMatrix,
            Player& player,
            glm::mat4 MVMatrix,
            GLint uMVMatrix,
            GLint uNormalMatrix,
            GLint uMVPMatrix,
            GLint uTexture,
            TextureManager& textureManager
        ){
		for(auto& cube : destructibleCube) {
			Cube::display(
	        			cube.position,
	        			cube.tex_id,
	        			ProjMatrix,
	        			player.getCamera(),
	        			MVMatrix,
	        			uMVMatrix,
	        			uNormalMatrix,
	        			uMVPMatrix,
	        			uTexture
	        			);
		}
	}

}