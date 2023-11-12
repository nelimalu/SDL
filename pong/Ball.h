#ifndef BALL_H
#define BALL_H

#include "graphics.h"

class Ball {
	private:
		double x;
		double y;
		int sidelength;
		int speed;
		int angle;

	public:
		Ball(double x, double y, int sidelength, int speed, int angle);
		void move();
		void draw(SDL_Renderer* renderer);
};


#endif