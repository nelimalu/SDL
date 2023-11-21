#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>

SDL_Rect* createRect(int x, int y, int width, int height);
void drawRect(SDL_Renderer* renderer, SDL_Rect* rectangle, int r, int g, int b);
int randint(int min, int max);
bool rectCollision(int x, int y, SDL_Rect* rect);

class Text {
	private:
		const char* text;
		int x;
		int y;
		int size;
		int default_red;
		int default_green;
		int default_blue;
		SDL_Color colour;
		SDL_Rect* rect;
		SDL_Texture* texture;
		TTF_Font* font;
		SDL_Renderer* renderer;

	public:
		Text(SDL_Renderer* renderer, const char* text, int x, int y, int size, int r, int g, int b);
		void draw();
		void update();
		void setText(const char* text);
		void setColour(int r, int g, int b);
		void hover(int x, int y, int r, int g, int b);
		SDL_Rect* getRect();
	
};

#endif