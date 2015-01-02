#include "glimac/Map.hpp"

namespace glimac {
	void Map::buildMap(TextureManager& textureManager) {
		destructibleCube.clear();
		undestructibleCube.clear();

		cv::Mat sea_ground;
		sea_ground = cv::imread("assets/Map/sea_ground.jpg", 1 );

    	// cv::Mat ground1;
    	// ground1 = cv::imread("../maps/ground1.jpg", 1 );

    	// cv::Mat ground2;
    	// ground2 = cv::imread("../maps/ground2.jpg", 1 );

    	// cv::Mat ground3;
    	// ground3 = cv::imread("../maps/ground3.jpg", 1 );


  //   	for(int x=0; x< sea_ground.rows; ++x) {
		// 	for(int y=0; y<sea_ground.cols; ++y) {
		// 		int posY = x - sea_ground.rows/2;
		// 		int posX = y - sea_ground.cols/2;
				
		// 		if ((int)sea_ground.at<cv::Vec3b>(x,y)[0] < (int)sea_ground.at<cv::Vec3b>(x,y)[2]) {		
		// 			undestructibleCube.push_back(glm::vec3(posX, 0, posY));
		// 		}
		// 		else{
		// 			undestructibleCube.push_back(glm::vec3(posX, 0, posY));
		// 		}
		// 	}
		// }

		for(int x=0; x< 20; ++x) {
			for(int y=0; y<20; ++y) {
				int posY = x - 20/2;
				int posX = y - 20/2;

				const Texture& texture = textureManager.get("assets/textures/brick.png");

				CubeAtom cubeAtom;
				cubeAtom.position = glm::vec3(posX, 0, posY);
				cubeAtom.tex_id = texture.getId();
				
				if ((int)sea_ground.at<cv::Vec3b>(x,y)[0] < (int)sea_ground.at<cv::Vec3b>(x,y)[2]) {
					undestructibleCube.push_back(cubeAtom);
				}
				else{
					undestructibleCube.push_back(cubeAtom);
				}
			}
		}

	}

	void Map::addCube(glm::ivec3 position, Texture &text){
			destructibleCube.push_back(glm::vec3(position));
	}

	void Map::display(
        glm::mat4 ProjMatrix,
        Player& player,
        glm::mat4 MVMatrix,
        GLint uMVMatrix,
        GLint uNormalMatrix,
        GLint uMVPMatrix,
        GLint uTexture,
        TextureManager textureManager
    ) {
    	float boundingCircleRadius = 20.0f;
    	float squareBoundingCircleRadius = boundingCircleRadius*boundingCircleRadius;

    	glm::vec3 playerPosition = player.getPosition();

        for(auto& cube : undestructibleCube) {
        	float xDiff = cube.position[0] - playerPosition[0];
        	float yDiff = cube.position[2] - playerPosition[2];

        	float squareDistanceToCube = xDiff*xDiff + yDiff*yDiff;
        	if(squareDistanceToCube < squareBoundingCircleRadius) {
        		Cube tmp(1, textureManager.get("assets/textures/brick.png"));
        		tmp.setPosition(cube.position);
        		tmp.display(ProjMatrix, player.getCamera(), MVMatrix, uMVMatrix, uNormalMatrix, uMVPMatrix, uTexture);
        	}
        }

       for(auto& x : destructibleCube) {
        	Cube tmp(1, textureManager.get("assets/textures/sand.jpg"));
        	tmp.setPosition(x);
        	tmp.display(ProjMatrix, camera, MVMatrix, uMVMatrix, uNormalMatrix, uMVPMatrix, uTexture);
        }
	}
}