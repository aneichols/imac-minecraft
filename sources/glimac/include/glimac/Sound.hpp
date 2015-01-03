#pragma once
#include <string.h>
#include <SDL/SDL_mixer.h>

namespace Pokecraft {

	enum Sounds {JUMP, DESTROY, BUILD, BACKGROUND}; //  0 1 2 3
	class Sound {

		int build();

		private:
			bool isEnabled = true;
			int nbSoundsEffects = 3;
			Mix_Music *backgroundMusic = NULL;
      Mix_Chunk *soundEffects[3];

		  std::string soundEffects_path[3] = {
		                   "assets/sounds/jump.wav",
		                   "assets/sounds/destroy_2.wav",
		                   "assets/sounds/build.wav",
		   };
		   void clean();

		public:
      Sound() {
          build();
      }
			void play(Sounds s);
			int  loadSounds();
			
			void setEnable(bool isEnabled);
			bool getEnable() const;
			~Sound();
	};
}
