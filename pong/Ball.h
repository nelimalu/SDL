#ifndef BALL_H
#define BALL_H

#include "graphics.h"
#include "Paddle.h"

class Ball {
	private:
		double x;
		double y;
		int sidelength;
		int speed;
		int angle;

	public:
		Ball(double x, double y, int sidelength, int speed, int angle);
		void move(Paddle* paddle1, Paddle* paddle2, int bounding_height);
		void draw(SDL_Renderer* renderer);
		void horizontal_bounce();
		void vertical_bounce();
};


#endif