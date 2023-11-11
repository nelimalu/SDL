#include <stdio.h>
#include <random>
#include <time.h>
#include "graphics.h"
#include "Paddle.h"
#include "Ball.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
const char* CAPTION = "PONG";


struct interface {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
};

interface setup() {
    interface screen;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    screen.window = SDL_CreateWindow(CAPTION, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen.renderer = SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED);

    return screen;
}


void cleanup(interface screen) {
	SDL_DestroyRenderer(screen.renderer);
	SDL_DestroyWindow(screen.window);  // Destroy window
	SDL_Quit();  // Quit SDL subsystems
}

int randint(int min, int max) {
	std::mt19937 rng(time(0));
	std::uniform_int_distribution<int> uni(0,359);
	return uni(rng);
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


void update(SDL_Renderer* renderer, Paddle* paddle1, Paddle* paddle2, Text* text, Ball* ball) {
	drawRect(renderer, NULL, 43, 46, 51);
	drawRect(renderer, createRect(SCREEN_WIDTH / 2, 70, 1, SCREEN_HEIGHT), 67, 74, 84);

	paddle1->draw(renderer);
	paddle2->draw(renderer);
	ball->draw(renderer);

	text->draw();
}


void mainloop(interface screen) {
	bool keys[] = {false, false, false, false};

	Paddle* paddle1 = new Paddle(10, 10, 5, 75, SCREEN_HEIGHT);
	Paddle* paddle2 = new Paddle(SCREEN_WIDTH - 15, 10, 5, 75, SCREEN_HEIGHT);

	int angle = randint(0, 359);
	printf("%d\n", angle);
	Ball* ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 2, angle);

	int x = 10;
	int y = 10;

	Text* text = new Text(screen.renderer, (char*) "PONG", 274, 2, 60, 67, 74, 84);
    
    
    bool run = true;
    SDL_Event event;
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
		ball->move();

		update(screen.renderer, paddle1, paddle2, text, ball);

		SDL_UpdateWindowSurface(screen.window);
		SDL_RenderPresent(screen.renderer);
		
    }
}


int main(int argc, char* args[]) {
	printf("[START] starting program\n");

	interface screen = setup();
	mainloop(screen);
	
	cleanup(screen);
	return 0;
}
