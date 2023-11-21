#include <stdio.h>
#include <random>
#include <time.h>
#include "graphics.h"
#include "Paddle.h"
#include "Ball.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
const char* CAPTION = "PONG";
int mouseX, mouseY;


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


void update(SDL_Renderer* renderer, Paddle* paddle1, Paddle* paddle2, Text* text, Ball* ball, Text* fps, Text* score1, Text* score2) {
	drawRect(renderer, NULL, 43, 46, 51);
	drawRect(renderer, createRect(SCREEN_WIDTH / 2, 95, 1, SCREEN_HEIGHT), 67, 74, 84);
	fps->draw();
	text->draw();
	score1->draw();
	score2->draw();

	paddle1->draw(renderer);
	paddle2->draw(renderer);
	ball->draw(renderer);
}


void update_titlescreen(SDL_Renderer* renderer, Text* title, Text* singleplayer_text, Text* multiplayer_text, Text* online_text) {
	drawRect(renderer, NULL, 43, 46, 51);

	title->draw();
	singleplayer_text->draw();
	multiplayer_text->draw();
	online_text->draw();
}


void updateMousePosition(interface screen) {
	int tempMouseX, tempMouseY, tempWindowX, tempWindowY;
	SDL_GetGlobalMouseState(&tempMouseX, &tempMouseY);
	SDL_GetWindowPosition(screen.window, &tempWindowX, &tempWindowY);
	mouseX = tempMouseX - tempWindowX;
	mouseY = tempMouseY - tempWindowY;
}



int titlescreen(interface screen) {
	Text* title = new Text(screen.renderer, (const char*) "PONG", SCREEN_WIDTH / 2, 20, 100, 255, 255, 255);
	Text* singleplayer_text = new Text(screen.renderer, (const char*) "< singleplayer >", SCREEN_WIDTH / 2, 150, 60, 240, 240, 240);
	Text* multiplayer_text = new Text(screen.renderer, (const char*) "< multiplayer >", SCREEN_WIDTH / 2, 220, 60, 240, 240, 240);
	Text* online_text = new Text(screen.renderer, (const char*) "< online >", SCREEN_WIDTH / 2, 290, 60, 240, 240, 240);

	bool run = true;
    SDL_Event event;
    while (run) {
    	while (SDL_PollEvent(&event)) {
    		switch (event.type) {
                case SDL_QUIT:
                    return 0;
                    break;

                case SDL_MOUSEMOTION:
                	updateMousePosition(screen);
                	break;

                case SDL_MOUSEBUTTONUP:
                	if (rectCollision(mouseX, mouseY, singleplayer_text->getRect()))
                		return 1;
                    if (rectCollision(mouseX, mouseY, multiplayer_text->getRect()))
                        return 2;
                	break;

                default:
                    break;
            }
    	}

    	if (rectCollision(mouseX, mouseY, singleplayer_text->getRect())) {
    		singleplayer_text->setColour(168, 168, 168);
    	} else {
    		singleplayer_text->setColour(255,255,255);
    	}

        

    	update_titlescreen(screen.renderer, title, singleplayer_text, multiplayer_text, online_text);

    	SDL_UpdateWindowSurface(screen.window);
		SDL_RenderPresent(screen.renderer);
    }

    return 0;
}	


void mainloop(interface screen, int gamemode) {
	bool keys[] = {false, false, false, false};

	Paddle* paddle1 = new Paddle(10, SCREEN_HEIGHT / 2 - 75 / 2, 5, 75, SCREEN_HEIGHT);
	Paddle* paddle2 = new Paddle(SCREEN_WIDTH - 15, SCREEN_HEIGHT / 2 - 75 / 2, 5, 75, SCREEN_HEIGHT);
	Ball* ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 0.5);

	int scores[2] = {0, 0}; 

	Text* text = new Text(screen.renderer, (const char*) "3", SCREEN_WIDTH / 2, 2, 60, 235, 181, 106);
	Text* fps_text = new Text(screen.renderer, (const char*) "--", SCREEN_WIDTH / 2, 65, 20, 67, 74, 84);
    Text* score_texts[2] = {
    	new Text(screen.renderer, (const char*) "0", SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - 75, 150, 67, 74, 84),
    	new Text(screen.renderer, (const char*) "0", SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 2 - 75, 150, 67, 74, 84)
    };

    int frames = 0;
    int prev_time = time(0);
    int start_time = time(0);
    bool run = true;
    SDL_Event event;
    while (run) {
    	SDL_Delay(1);
    	
    	frames++;
    	if (prev_time < time(0)) {
    		prev_time = time(0);
    		fps_text->setText((std::to_string(frames) + " fps").c_str());
    		frames = 0;
    	}

    	while (SDL_PollEvent(&event)) {
    		switch (event.type) {
                case SDL_KEYDOWN:
                	handle_keypress(event.key, keys, true);
                	break;
                case SDL_KEYUP:
                    handle_keypress(event.key, keys, false);
                    break;

                case SDL_QUIT:
                    run = false;
                    break;

                case SDL_MOUSEMOTION:
                	SDL_GetGlobalMouseState(&mouseX, &mouseY);
                	break;

                default:
                    break;
            }
    	}

        if (time(0) < start_time + 4) {
            text->setText(std::to_string(start_time + 4 - time(0)).c_str());
        } else {
            if (time(0) == start_time + 4) {
                text->setText((const char*) "PONG");
                text->setColour(67, 74, 84);
            }
            paddle1->move(new bool[2] {keys[0], keys[1]});

            if (gamemode == 1)
                paddle2->move(ball->getY());
            if (gamemode == 2)
                paddle2->move(new bool[2] {keys[2], keys[3]});

            ball->move(SCREEN_HEIGHT);
            int point = ball->handle_collision(paddle1, paddle2, SCREEN_WIDTH);
            if (point != -1)
                score_texts[point]->setText(std::to_string(++scores[point]).c_str());
        }
		
		
		update(screen.renderer, paddle1, paddle2, text, ball, fps_text, score_texts[0], score_texts[1]);

		SDL_UpdateWindowSurface(screen.window);
		SDL_RenderPresent(screen.renderer);
		
    }
}


int main(int argc, char* args[]) {
	printf("[START] starting program\n");

	interface screen = setup();

	int gamemode = titlescreen(screen);

	mainloop(screen, gamemode);
	
	cleanup(screen);
	return 0;
}
