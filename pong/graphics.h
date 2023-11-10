#ifndef GRAPHICS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h>

SDL_Rect* createRect(int x, int y, int width, int height);
void drawRect(SDL_Renderer* renderer, SDL_Rect* rectangle, int r, int g, int b);

class Text {
	private:
		char* text;
		int x;
		int y;
		int size;
		SDL_Color colour;
		SDL_Rect* rect;
		SDL_Texture* texture;
		TTF_Font* font;
		SDL_Renderer* renderer;

	public:
		Text(SDL_Renderer* renderer, char* text, int x, int y, int size, int r, int g, int b);
		void draw();

	
};

#endif