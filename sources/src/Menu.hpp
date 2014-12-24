#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include "Sound.hpp"

namespace Pokecraft {

	enum State {SETTINGS, CHOOSEPLAYER, ROOT, GAME}; //  0 1 2

	class Menu
	{
		private:
			bool isEnabled;
			Sound soundPlayer;
			State state = ROOT;

		public:
			Menu(Sound &s);
			bool getEnabled();
			State getState();
			void setEnabled(bool enabled);
			void setSound(bool enabled);
			void updateMenu();
			void displayMenu();
			void launchGame();
			void setState(State s);
			void loadMap(std::string path);
	};
}

#endif
/*
class Menu
{
    public:
        Menu();
        ~Menu();
        void afficher(void);
        void clic(void);
        string afficheConsole(string nomFichier);
 
    private:
        string fondMenu;
};
 
#endif // MENU_H_INCLUDED
*/