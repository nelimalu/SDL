#include <SDL2.h>
#include <stdio.h>
#include <typeinfo>
#include "graphics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* CAPTION = "wooooo";
const int SPEED = 1;
const int PLAYER_WIDTH = 30;
const int PLAYER_HEIGHT = 30;


SDL_Window* setup() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		printf("[ERROR] failed to load SDL :: %s\n", SDL_GetError());
		return NULL;
	}

	SDL_Window* window = SDL_CreateWindow(CAPTION, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	
	if (window == NULL)
		printf("[ERROR] Window could not be created! SDL_Error: %s\n", SDL_GetError());

	return window;
}


void cleanup(SDL_Window* window) {
	SDL_DestroyWindow(window);  // Destroy window
	SDL_Quit();  // Quit SDL subsystems
}


void handle_keypress(SDL_KeyboardEvent key, bool keys[4], bool down) {
	SDL_Keycode keycode = key.keysym.sym;
	//printf("[INPUT] keypress: %s\n", SDL_GetKeyName(key.keysym.sym));
	//printf("%d %d %d %d\n", keys[0], keys[1], keys[2], keys[3]);

	switch (keycode) {
		case SDLK_w:
			keys[0] = down;
			break;
		case SDLK_s:
			keys[1] = down;
			break;
		case SDLK_a:
			keys[2] = down;
			break;
		case SDLK_d:
			keys[3] = down;
			break;
	}
}


void move_player(int* x, int* y, bool keys[4]) {
	if (keys[0])
		*y -= SPEED;
	if (keys[1])
		*y += SPEED;
	if (keys[2])
		*x -= SPEED;
	if (keys[3])
		*x += SPEED;

	if (*x < 0)
		*x = 0;
	else if ((*x + PLAYER_WIDTH) > SCREEN_WIDTH)
		*x = SCREEN_WIDTH - PLAYER_WIDTH;
	if (*y < 0)
		*y = 0;
	else if ((*y + PLAYER_HEIGHT) > SCREEN_HEIGHT)
		*y = SCREEN_HEIGHT - PLAYER_HEIGHT;
}



void mainloop(SDL_Window* window, SDL_Surface* screenSurface) {
	bool keys[] = {false, false, false, false};

	int x = 10;
	int y = 10;
    
    SDL_Event event;
    bool run = true;
    while (run) {
    	SDL_Delay(1);
    	while (SDL_PollEvent(&event)) {
    		switch (event.type){
                case SDL_KEYDOWN:
                	handle_keypress(event.key, keys, true);
                	break;
                case SDL_KEYUP:
                    handle_keypress(event.key, keys, false);
                    break;

                case SDL_QUIT:
                    run = false;
                    break;

                default:
                    break;
            }
    	}

    	move_player(&x, &y, keys);

		drawRect(screenSurface, NULL, 240, 240, 240);  // fill screen
		drawRect(screenSurface, createRect(x, y, PLAYER_WIDTH, PLAYER_HEIGHT), 217, 101, 93);

		SDL_UpdateWindowSurface(window);  // update the surface
    }
}


int main(int argc, char* args[]) {
	printf("[START] starting program\n");

	SDL_Surface* screenSurface = NULL;  // the surface contained by the window
	SDL_Window* window = setup();  // the window we'll be rendering to
	
	if (window != NULL)
		mainloop(window, SDL_GetWindowSurface(window));
	
	cleanup(window);
	return 0;
}
