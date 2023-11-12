#include "Ball.h"
#include <stdio.h>

Ball::Ball(double x, double y, int sidelength, int speed, int angle) {
	this->x = x;
	this->y = y;
	this->sidelength = sidelength;
	this->speed = speed;
	this->angle = angle;
}

void Ball::horizontal_bounce() {
	angle = (540 - angle) % 360;
}

void Ball::vertical_bounce() {
	angle = (360 - angle) % 360;
}

void Ball::move(Paddle* paddle1, Paddle* paddle2, int bounding_height) {
	x += cos((double) (angle * 3.1415 / 180)) * speed;
	y += sin((double) (angle * 3.1415 / 180)) * speed;

	if (x < 0) {
		x = 0;
		horizontal_bounce();
	}
	if (x > 640) {  // todo change from 640
		x = 640;
		horizontal_bounce();
	}
	if (y < 0) {
		y = 0;
		vertical_bounce();
	}
	if (y > bounding_height) {
		y = bounding_height;
		vertical_bounce();
	}
}


void Ball::draw(SDL_Renderer* renderer) {
	drawRect(renderer, createRect((int) x, (int) y, sidelength, sidelength), 255, 255, 255);
}
