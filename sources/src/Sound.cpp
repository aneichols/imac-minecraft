#include <iostream>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include "Sound.hpp"
#include <SDL/SDL_mixer.h>

namespace Pokecraft {

	int Sound::build() {

    if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        std::cout << "SOUND ERROR" << std::endl;
        return -1;
    }
    loadSounds();
		return 0;
	}

	void Sound::play(Sounds s){
		if (!isEnabled){return;}
		if(s == 3){Mix_PlayMusic( backgroundMusic, -1 );}
		else Mix_PlayChannel( -1, soundEffects[s], 0 );
	}

	void Sound::setEnable(bool enabled){

		if(enabled == false && this->isEnabled == true){
			 Mix_HaltMusic();
		}else if (enabled == true && this->isEnabled == false){
			Mix_PlayMusic( backgroundMusic, -1 );
		}
		this->isEnabled = enabled;
	}

	bool Sound::getEnable()const{
		return isEnabled;
	}

	int Sound::loadSounds(){
		backgroundMusic = Mix_LoadMUS("assets/sounds/pkrs_littleroot.mid");
		if( backgroundMusic == NULL ) {
    	std::cout << "assets/sounds/pkrs_littleroot.mid not found" << std::endl;
    	return 0;
    }

		for(int i = 0; i < nbSoundsEffects; i++){
			soundEffects[i] = Mix_LoadWAV(soundEffects_path[i].c_str());
			if( soundEffects[i] == NULL ) {
	    	std::cout << soundEffects_path[i] << "not found" << std::endl;
	    	return -1;
    	}
		}
		return 0;
	}

	void Sound::clean(){
		 //Free the sound effects
		for(int i = 0; i < nbSoundsEffects; i++){
			Mix_FreeChunk(soundEffects[i]);
		}
		 //Free the music
		 Mix_FreeMusic( backgroundMusic );
		//Quit SDL_mixer
		 Mix_CloseAudio();
	}

	Sound::~Sound() {
		this->clean();
	}
}
