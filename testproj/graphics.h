#ifndef GRAPHICS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define GRAPHICS_H

#include <SDL.h>

SDL_Rect* createRect(int x, int y, int width, int height);
void drawRect(SDL_Surface* screenSurface, SDL_Rect* rectangle, int r, int g, int b);

#endif