#include "Menu.hpp"
#include <glimac/Image.hpp>
#include <fstream>


using namespace std;

Menu::Menu() : fondMenu()
{}
 
Menu::Menu(string fondMenu) : fondMenu(fondMenu)
{}

void Menu::afficher()
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

}