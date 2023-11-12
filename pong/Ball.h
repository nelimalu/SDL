#ifndef BALL_H
#define BALL_H

#include "graphics.h"
#include "Paddle.h"

class Ball {
	private:
		double x;
		double y;
		int sidelength;
		double speed;
		int angle;
		bool gone;

	public:
		Ball(double x, double y, int sidelength, double speed, int angle);
		void move(Paddle* paddle1, Paddle* paddle2, int bounding_width, int bounding_height);
		void draw(SDL_Renderer* renderer);
		void horizontal_bounce();
		void vertical_bounce();
		void handle_collision(Paddle* paddle1, Paddle* paddle2, int bounding_width);
		void reset();
};


#endif