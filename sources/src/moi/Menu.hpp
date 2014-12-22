#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <new>
#include "Bouton.hpp"
#include <string>

using namespace std;
 
class Menu
{
    public:
        Menu();
        Menu(string fondMenu);
        ~Menu();
        void afficher(void);
        void clic(void);
        string afficheConsole(string nomFichier);
 
    private:
        string fondMenu;
};
 
#endif // MENU_H_INCLUDED

