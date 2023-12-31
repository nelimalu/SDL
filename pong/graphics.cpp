#include "graphics.h"
#include <stdio.h>
#include <random>
#include <time.h>

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

int randint(int min, int max) {
	std::mt19937 rng(time(0));
	std::uniform_int_distribution<int> uni(min,max);
	return uni(rng);
}

bool rectCollision(int x, int y, SDL_Rect* rect) {
	return x >= rect->x && x <= rect->x + rect->w && y >= rect->y && y <= rect->y + rect->h;
}


Text::Text(SDL_Renderer* renderer, const char* text, int x, int y, int size, int r, int g, int b) {
	this->text = text;
	this->x = x;
	this->y = y;
	this->size = size;
	this->renderer = renderer;
	this->default_red = r;
	this->default_blue = b;
	this->default_green = g;
	font = TTF_OpenFont("assets/BebasNeue-Regular.ttf", size);
	setColour(r, g, b);
}

void Text::setText(const char* text) {
	this->text = text;
	update();
}

void Text::setColour(int r, int g, int b) {
	colour = {(uint8_t)(r), (uint8_t)(g), (uint8_t)(b)};
	update();
}

void Text::update() {
	rect = createRect(x, y, 0, 0);
	TTF_SizeText(font, text, &rect->w, &rect->h);
	rect->x -= rect->w / 2;
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, colour); 
	texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
}

void Text::hover(int x, int y, int r, int g, int b) {
	if (rectCollision(x, y, getRect()))
		setColour(r, g, b);
	else
		setColour(default_red, default_green, default_blue);
}

void Text::draw() {
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

SDL_Rect* Text::getRect() {
	return rect;
}

