#include "graphics.h"

SDL_Rect* createRect(int x_, int y_, int width, int height) {
	SDL_Rect* rect = new SDL_Rect;
	rect->x = x_;
	rect->y = y_;
	rect->w = width;
	rect->h = height;

	return rect;
}

void drawRect(SDL_Surface* screenSurface, SDL_Rect* rectangle, int r, int g, int b) {
	SDL_FillRect(screenSurface, rectangle, SDL_MapRGB(screenSurface->format, r, g, b));
}
