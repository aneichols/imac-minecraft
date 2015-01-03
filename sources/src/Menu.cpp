#include <glimac/Image.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "Sound.hpp"
#include "Menu.hpp"

using namespace glimac;

namespace Pokecraft {

	Menu::Menu(Sound &s){
		this->soundPlayer = s;
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

	void Menu::updateMenu(){
		switch (state){
			case 0 :
				break;
			case 1 :
				break;
			case 2 :
				break;
		}
		displayMenu();
	}

	void Menu::launchGame(){
		this->isEnabled = false;
		soundPlayer.play(BACKGROUND);
	}

	void Menu::displayMenu(){

		switch (menu.getState()){
			case 0 : //SETTINGS
			//affiche settingTexture
			break;

			case 1 : //CHOOSEPLAYER
			// affiche choosePlayerTexture
			break;

			case 2 : //ROOT
			//affiche rootTexture
			break; 


		// glGenBuffers (1, &vbo);
	 	// glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Vertex2DColor vertices1[] = { 
		//     Vertex2DColor(glm::vec2(-1, 1), glm::vec3(1,0,0)), // premier sommet
		//     Vertex2DColor(glm::vec2(-1, -1), glm::vec3(0,1,0)), // deuxième sommet
		//     Vertex2DColor(glm::vec2(1, 1), glm::vec3(0,0,1)), // troisième sommet

		//     Vertex2DColor(glm::vec2(1, 1), glm::vec3(1,0,0)), // premier sommet
		//     Vertex2DColor(glm::vec2(1, -1), glm::vec3(0,1,0)), // deuxième sommet
		//     Vertex2DColor(glm::vec2(-1, -1), glm::vec3(0,0,1)) // troisième sommet
		// };

		// glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices1, GL_STATIC_DRAW);
		// glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Menu::loadMap(std::string path){}
}

/*
void Menu::display()
{

}



string Menu::afficheConsole(string nomFichier)
{
	string retour;

	/////// ACCUEIL //////////////////////////////////////////////////////////////////////////////////////
	ifstream fichier("accueil.txt", ios::in);  // on ouvre le fichier en lecture
 
        if(fichier)
        {       
        	fichier.close();  // on ferme le fichier
        }
        else
            cerr << "Impossible d'ouvrir le fichier !" << endl;

        string saisie;
        cin >> saisie;
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //////// "JOUER" //////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        if saisie == "j") 
        {
        	//choix du monde !
        	ifstream fichier("monde.txt", ios::in);
 
	        if(fichier)
	        {       
	        	fichier.close(); 
	        }
	        else
	            cerr << "Impossible d'ouvrir le fichier !" << endl;

	        string saisie2;
        	cin >> saisie2;

        	if(saisie2 == "jadiel")
        	{
        		ifstream fichier("confirmation.txt", ios::in);
 
		        if(fichier)
		        {       
		        	fichier.close(); 
		        }
		        else
		            cerr << "Impossible d'ouvrir le fichier !" << endl;

		        string saisie3;
		        cin >> saisie3;

		        if(saisie3 == "o")
		        {
		        	retour = "jadiel";
		        }
		        if (saisie3 == "n")
		        {
		        	// retour
		        	// ?
		        }
	        }

        	if(saisie2 == "jotho")
        	{	
        		ifstream fichier("confirmation.txt", ios::in);
 
		        if(fichier)
		        {       
		        	fichier.close(); 
		        }
		        else
		            cerr << "Impossible d'ouvrir le fichier !" << endl;

		        string saisie3;
		        cin >> saisie3;

		        if(saisie3 == "o")
		        {
		        	retour ="jotho";
		        }
		        if (saisie3 == "n")
		        {
		        	// retour
		        	// ?
		        }
        	}

        	if(saisie2 == "bourg-palette" || saisie2 == "bourg palette")
        	{	
        		ifstream fichier("confirmation.txt", ios::in);
 
		        if(fichier)
		        {       
		        	fichier.close(); 
		        }
		        else
		            cerr << "Impossible d'ouvrir le fichier !" << endl;

		        string saisie3;
		        cin >> saisie3;

		        if(saisie3 == "o")
		        {
		        	retour = "bourg";
		        }
		        if (saisie3 == "n")
		        {
		        	// retour
		        	// ?
		        }
        	}
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////
        //////// "OPTIONS" //////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        if saisie == "o")
        {
        	ifstream fichier("options.txt", ios::in);
 
	        if(fichier)
	        {       
	        	fichier.close(); 
	        }
	        else
	            cerr << "Impossible d'ouvrir le fichier !" << endl;

	        string saisie2;
	        cin >> saisie2;

	        ////////////////////////////
	        //////// "COMMANDES" ///////
	        ////////////////////////////
	        if (saisie2 == "c")
	        {
	        	
	        	ifstream fichier("commandes.txt", ios::in);
	 
		        if(fichier)
		        {       
		        	fichier.close(); 
		        }
		        else
		            cerr << "Impossible d'ouvrir le fichier !" << endl;
		        }

		        string saisie3;
	        	cin >> saisie3;
	        	if (saisie3 == "r")
	        	{
	        		//retour
	        		// ?
	        	}
	        }
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////
        //////// "QUITTER" //////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        if saisie== "q")
        {
        	//on quitte !
        }

        return retour;
}




void Menu::clic()
{

}*/