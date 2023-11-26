#include "SDL_gpu.h"
#include <stdlib.h>


int main(int argc, char *argv[]) {
	GPU_Target* screen = GPU_Init(800, 600, GPU_DEFAULT_INIT_FLAGS);

	if (screen == NULL)
		return 3;


	SDL_Event event;
	bool run = true;
	while (run) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				run = false;
		}

		GPU_ClearRGBA(screen, 240, 240, 240, 255);
		GPU_Flip(screen);

	}

	GPU_Quit();

	return 0;
}