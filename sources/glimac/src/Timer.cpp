
#include "glimac/Timer.hpp"

namespace Pokecraft {

	void Timer::resetTimer() {
		start = SDL_GetTicks();
	}

	Timer::Timer(int fps): frameDuration(1000 / fps) {
		resetTimer();
	}

	void Timer::sleepUntilNextTick() {
		Uint32 currentTime = SDL_GetTicks();
		Uint32 delta = currentTime - start;

		if(delta < frameDuration) {
			SDL_Delay(frameDuration - delta);
		}

		resetTimer();
	}

}


