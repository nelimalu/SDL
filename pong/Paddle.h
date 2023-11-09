#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

class Paddle {
	private:
		int x;
		int y;
		int width;
		int height;
		int boundingHeight;
		int colour[3] = {255, 255, 255};

	public:
		static const int speed = 1;

		Paddle(int x, int y, int width, int height, int boundingHeight);
		void move(bool keys[4]);
		void draw(SDL_Surface* screenSurface);
};

#endif