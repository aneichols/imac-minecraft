#include <opencv2/opencv.hpp>
#include <vector>
#include "FreeflyCamera.hpp"
#include "common.hpp"
#include "Cube.hpp"
#include "Player.hpp"
#include <glimac/glm.hpp>
#include <glimac/TextureManager.hpp>



namespace glimac {

	class Map{
	private:
		struct CubeAtom {
			glm::vec3 position;
			GLuint tex_id;
		};

		std::vector<CubeAtom> destructibleCube;
		std::vector<CubeAtom> undestructibleCube;

		void buildMap(TextureManager& textureManager);

	public:
		Map(TextureManager& textureManager) {
			buildMap(textureManager);
		}
		
		void display(
            glm::mat4 ProjMatrix,
            Player& player,
            glm::mat4 MVMatrix,
            GLint uMVMatrix,
            GLint uNormalMatrix,
            GLint uMVPMatrix,
            GLint uTexture,
            TextureManager textureManager
        );
	};

}