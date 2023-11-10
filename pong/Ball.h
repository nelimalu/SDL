#ifndef BALL_H
#define BALL_H

#include "graphics.h"

class Ball {
	private:
		int x;
		int y;
		int sidelength;
		int speed;
		float angle;

	public:
		Ball(int x, int y, int sidelength, int speed, float angle);
		void move();
		void draw(SDL_Renderer* renderer);
};


#endif