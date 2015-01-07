#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <glimac/Sound.hpp>

using namespace glimac;

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
			void setState(State s);
			void setSound(bool enabled);
			void displayMenu();
			void updateMenu();
			void launchGame();
			void loadMap(std::string path);
	};
}
