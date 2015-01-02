#include <opencv2/opencv.hpp>
#include <vector>
#include "FreeflyCamera.hpp"
#include "common.hpp"
#include "Cube.hpp"
#include <glimac/glm.hpp>
#include <glimac/TextureManager.hpp>



namespace glimac {

	class Map{
		private:
		std::vector<glm::vec3> destructibleCube;
		std::vector<glm::vec3> undestructibleCube;

		void buildMap();

	public:
		Map() {
			buildMap();
		}
		
		void addCube(glm::ivec3 position, Texture &text);

		void display(
            glm::mat4 ProjMatrix,
            FreeflyCamera camera,
            glm::mat4 MVMatrix,
            GLint uMVMatrix,
            GLint uNormalMatrix,
            GLint uMVPMatrix,
            GLint uTexture,
            TextureManager textureManager
        );
	};

}