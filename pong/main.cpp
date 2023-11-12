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

struct scores {
	int score1 = 0;
	int score2 = 0;
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


void update(SDL_Renderer* renderer, Paddle* paddle1, Paddle* paddle2, Text* text, Ball* ball, Text* fps) {
	drawRect(renderer, NULL, 43, 46, 51);
	drawRect(renderer, createRect(SCREEN_WIDTH / 2, 70, 1, SCREEN_HEIGHT), 67, 74, 84);
	fps->draw();

	paddle1->draw(renderer);
	paddle2->draw(renderer);
	ball->draw(renderer);

	text->draw();
}


void mainloop(interface screen) {
	bool keys[] = {false, false, false, false};

	Paddle* paddle1 = new Paddle(10, 10.0, 5, 75, SCREEN_HEIGHT);
	Paddle* paddle2 = new Paddle(SCREEN_WIDTH - 15, 10, 5, 75, SCREEN_HEIGHT);

	int angle = randint(0, 359);
	Ball* ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 0.5, angle);

	int x = 10;
	int y = 10;

	Text* text = new Text(screen.renderer, (const char*) "PONG", 274, 2, 60, 67, 74, 84);
	Text* fps_text = new Text(screen.renderer, (const char*) "0", 0, SCREEN_HEIGHT - 20, 20, 67, 74, 84);
    
    int frames = 0;
    int prev_time = time(0);
    bool run = true;
    SDL_Event event;
    while (run) {
    	SDL_Delay(1);
    	
    	frames++;
    	if (prev_time < time(0)) {
    		prev_time = time(0);
    		fps_text = new Text(screen.renderer, (std::to_string(frames) + "fps").c_str(), 0, SCREEN_HEIGHT - 20, 20, 67, 74, 84);
    		frames = 0;
    	}

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
		ball->move(paddle1, paddle2, SCREEN_WIDTH, SCREEN_HEIGHT);

		update(screen.renderer, paddle1, paddle2, text, ball, fps_text);

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
