#include "glimac/Map.hpp"
#include <cmath>

namespace glimac {

	static bool areColorComponentsEqual(int component1, int component2, int threshold = 10) {
		return abs(component2 - component1) < threshold;
	}

	static bool areColorsEqual(cv::Vec3b color1, cv::Vec3b color2, int threshold = 100) {
		return
			areColorComponentsEqual(color1[0], color2[0], threshold) &&
			areColorComponentsEqual(color1[1], color2[1], threshold) &&
			areColorComponentsEqual(color1[2], color2[2], threshold);
	}

	void Map::buildLevel(std::string path, TextureManager& textureManager, unsigned int levelNumber) {
		cv::Mat level = cv::imread(path, 1);

		for(int x=0; x < level.rows; ++x) {
		 	for(int y=0; y < level.cols; ++y) {
		 		int posY = y - level.cols/2;
		 		int posX = x - level.rows/2;

				CubeAtom cubeAtom;
				cubeAtom.position = glm::vec3(posX, levelNumber, posY);
				cubeAtom.moveThrough = false;

				cv::Vec3b colorRed(254, 0, 0),
					colorGreen(0, 254, 0),
					colorBlue(0, 0, 254);

				cv::Vec3b color = level.at<cv::Vec3b>(x, y);

				switch(levelNumber) {

				case 0:
					if(areColorsEqual(color, colorRed)) {
						const Texture& texture = textureManager.get("assets/textures/sand.jpg");
						cubeAtom.tex_id = texture.getId();

						undestructibleCube.push_back(cubeAtom);
					} else { // if(areColorsEqual(color, colorBlue)) {
						const Texture& texture = textureManager.get("assets/textures/water.png");
						cubeAtom.tex_id = texture.getId();
						cubeAtom.moveThrough = true;

						undestructibleCube.push_back(cubeAtom);
					}
					break;

				case 1:
					if(areColorsEqual(color, colorRed)) {
						const Texture& texture = textureManager.get("assets/textures/sand.jpg");
						cubeAtom.tex_id = texture.getId();

						destructibleCube.push_back(cubeAtom);
					}
					break;

				case 2:
					if(areColorsEqual(color, colorRed)) {
						const Texture& texture = textureManager.get("assets/textures/herbe.jpg");
						cubeAtom.tex_id = texture.getId();

						destructibleCube.push_back(cubeAtom);
					}
					break;

				default:
					if(areColorsEqual(color, colorRed)) {
						const Texture& texture = textureManager.get("assets/textures/rock.png");
						cubeAtom.tex_id = texture.getId();

						destructibleCube.push_back(cubeAtom);
					}
					break;
				}
			}
		}
	}

	void Map::buildMap(TextureManager& textureManager) {
		destructibleCube.clear();
		undestructibleCube.clear();

		buildLevel("assets/Map/sea_ground.jpg", textureManager, 0);
		buildLevel("assets/Map/ground1.jpg", textureManager, 3);
		buildLevel("assets/Map/ground2.jpg", textureManager, 2);
		buildLevel("assets/Map/ground3.jpg", textureManager, 1);
	}

	void Map::addCube(glm::ivec3 position, const Texture &text){
		CubeAtom cubeAtom;
		cubeAtom.position = glm::vec3(position);
		cubeAtom.tex_id = text.getId();
		destructibleCube.push_back(cubeAtom);
	}

	void Map::destroyCube(glm::ivec3 position){
		int i = 0;
		for(auto& cube : destructibleCube) {
			i++;

			if(	cube.position.x == position.x &&
					cube.position.y == position.y &&
					cube.position.z == position.z
				){

					destructibleCube.erase(destructibleCube.begin() + i);
					return;
				}
    }
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
    	float boundingCircleRadius = 30.0f;
    	float squareBoundingCircleRadius = boundingCircleRadius*boundingCircleRadius;

    	glm::vec3 playerPosition = player.getPosition();

    	// only display the cubes located within a radius of 20
        for(auto& cube : undestructibleCube) {
        	float xDiff = cube.position[0] - playerPosition[0];
        	float yDiff = cube.position[2] - playerPosition[2];

        	float squareDistanceToCube = xDiff*xDiff + yDiff*yDiff;
        	if(squareDistanceToCube < squareBoundingCircleRadius) {
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

        for(auto& cube : destructibleCube) {
        	float xDiff = cube.position[0] - playerPosition[0];
        	float yDiff = cube.position[2] - playerPosition[2];

        	float squareDistanceToCube = xDiff*xDiff + yDiff*yDiff;
        	if(squareDistanceToCube < squareBoundingCircleRadius) {
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

 				for(auto& cube : destructibleCube) {
        	float xDiff = cube.position[0] - playerPosition[0];
        	float yDiff = cube.position[2] - playerPosition[2];

        	float squareDistanceToCube = xDiff*xDiff + yDiff*yDiff;
        	if(squareDistanceToCube < squareBoundingCircleRadius) {
        		Cube tmp(1, textureManager.get("assets/textures/brick.png"));
        		tmp.setPosition(cube.position);
        		tmp.display(ProjMatrix, player.getCamera(), MVMatrix, uMVMatrix, uNormalMatrix, uMVPMatrix, uTexture);
        	}
        }
	}
}