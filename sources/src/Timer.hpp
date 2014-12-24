
#ifndef HPP_TIMER
#define HPP_TIMER

#include <SDL/SDL.h>

namespace Pokecraft {
	class Timer {
		Uint32 start;
		Uint32 frameDuration;

		void resetTimer();

	public:
		Timer(int fps);

		void sleepUntilNextTick();
	};
}

#endif

