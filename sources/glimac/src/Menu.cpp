
#include <glimac/Image.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sound.hpp>
#include <glimac/Interface.hpp>
#include <glimac/Menu.hpp>

using namespace glimac;

namespace Pokecraft {

	Menu::Menu(){
		std::cout << "menu builded" << std::endl;
	}

	bool Menu::getEnabled(){
		return isEnabled;
	}

	State Menu::getState(){
		return state;
	}

	void Menu::setEnabled(bool enabled){
		this->isEnabled = enabled;
	}

	void Menu::setSound(bool enabled){
		this->soundPlayer.setEnable(enabled);
	}

	void Menu::setState(State s){
		this->state = s;
	}

	// void Menu::updateMenu(){
	// 	switch (state){
	// 		case 0 :
	// 			break;
	// 		case 1 :
	// 			break;
	// 		case 2 :
	// 			break;
	// 	}
	// 	displayMenu();
	// }

	void Menu::displayMenu(){
		this->soundPlayer.play(BUILD);

		switch (this->state){
			case 0 : //SETTINGS
			//affiche settingTexture
			DrawImage(0.0f, 0.0f, 800, 600, "assets/textures/accueil.png");
			break;

			case 1 : //CHOOSEPLAYER
			// affiche choosePlayerTexture
			DrawImage(0.0f, 0.0f, 800, 600, "assets/textures/choose_player.png");
			break;

			case 2 : //ROOT
			//affiche rootTexture
			DrawImage(0.0f, 0.0f, 800, 600, "assets/textures/accueil.png");
			break; 
		}
	}

	void Menu::launchGame(){
		this->isEnabled = false;
	}
}

