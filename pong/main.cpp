#include <SDL.h>
#include <stdio.h>
#include <typeinfo>
#include "graphics.h"
#include "Paddle.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
const char* CAPTION = "PONG";


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
	switch (key.keysym.sym) {
		case SDLK_w:
			keys[0] = down;
			break;
		case SDLK_s:
			keys[1] = down;
			break;
		case SDLK_UP:
			keys[2] = down;
			break;
		case SDLK_DOWN:
			keys[3] = down;
			break;
	}
}


void update(SDL_Surface* screenSurface, Paddle* paddle1, Paddle* paddle2) {
	// highlight #434a54
	drawRect(screenSurface, NULL, 43, 46, 51);
	drawRect(screenSurface, createRect(SCREEN_WIDTH / 2, 0, 1, SCREEN_HEIGHT), 67, 74, 84);


	

	paddle1->draw(screenSurface);
	paddle2->draw(screenSurface);
}


void mainloop(SDL_Window* window, SDL_Surface* screenSurface) {
	bool keys[] = {false, false, false, false};

	Paddle* paddle1 = new Paddle(10, 10, 5, 75, SCREEN_HEIGHT);
	Paddle* paddle2 = new Paddle(SCREEN_WIDTH - 20, 10, 5, 75, SCREEN_HEIGHT);

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

		paddle1->move(new bool[2] {keys[0], keys[1]});
		paddle2->move(new bool[2] {keys[2], keys[3]});

		update(screenSurface, paddle1, paddle2);
		SDL_UpdateWindowSurface(window);
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
