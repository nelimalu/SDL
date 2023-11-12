#include "Ball.h"
#include "Paddle.h"
#include <stdio.h>

Ball::Ball(double x, double y, int sidelength, int speed, int angle) {
	this->x = x;
	this->y = y;
	this->sidelength = sidelength;
	this->speed = speed;
	this->angle = angle;
}

void Ball::move() {
	x += cos((double) (angle * 3.1415 / 180)) * speed;
	y += sin((double) (angle * 3.1415 / 180)) * speed;

	if (x < 0) {
		x = 0;
		angle = (540 - angle) % 360;
	}
	if (x < 0) {
		x = 0;
		angle = (540 - angle) % 360;
	}
}


void Ball::draw(SDL_Renderer* renderer) {
	drawRect(renderer, createRect((int) x, (int) y, sidelength, sidelength), 255, 255, 255);
}
