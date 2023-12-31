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
		double initialSpeed;
		int angle;
		bool gone;

	public:
		Ball(double x, double y, int sidelength, double speed);
		void move(int bounding_height);
		void draw(SDL_Renderer* renderer);
		void horizontal_bounce();
		void vertical_bounce();
		int handle_collision(Paddle* paddle1, Paddle* paddle2, int bounding_width);
		void reset();
		void initAngle();
		void speedUp();
		int getY();
};


#endif