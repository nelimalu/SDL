#ifndef GRAPHICS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_events.h>

SDL_Rect* createRect(int x, int y, int width, int height);
void drawRect(SDL_Surface* screenSurface, SDL_Rect* rectangle, int r, int g, int b);

class Text {
	private:
		char* text;
		int x;
		int y;
		int size;

	public:
		Text(char* text, int x, int y, int size);
		void draw(SDL_Surface* screenSurface);

	/*
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);


	SDL_Color White = {255, 255, 255};


	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); 


	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);*/
};

#endif