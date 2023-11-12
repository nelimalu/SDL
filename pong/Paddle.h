#ifndef PADDLE_H
#define PADDLE_H

#include "graphics.h"

class Paddle {
	private:
		int x;
		double y;
		int width;
		int height;
		int boundingHeight;
		int colour[3] = {255, 255, 255};

	public:
		static constexpr double speed = 0.5;

		Paddle(int x, double y, int width, int height, int boundingHeight);
		void move(bool keys[4]);
		void draw(SDL_Renderer* renderer);
		int getX();
		int getY();
		int getWidth();
		int getHeight();
};

#endif