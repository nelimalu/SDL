#include "graphics.h"
#include <stdio.h>

SDL_Rect* createRect(int x_, int y_, int width, int height) {
	SDL_Rect* rect = new SDL_Rect;
	rect->x = x_;
	rect->y = y_;
	rect->w = width;
	rect->h = height;

	return rect;
}

void drawRect(SDL_Renderer* renderer, SDL_Rect* rectangle, int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, rectangle);
}


Text::Text(SDL_Renderer* renderer, char* text, int x, int y, int size, int r, int g, int b) {
	this->text = text;
	this->x = x;
	this->y = y;
	this->size = size;
	this->renderer = renderer;

	font = TTF_OpenFont("assets/BebasNeue-Regular.ttf", size);
	colour = {(uint8_t)(r), (uint8_t)(g), (uint8_t)(b)};
	rect = createRect(x, y, 0, 0);
	TTF_SizeText(font, text, &rect->w, &rect->h);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, colour); 
	texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

}

void Text::draw() {
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

