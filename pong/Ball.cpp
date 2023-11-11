#include "Ball.h"
#include <stdio.h>

Ball::Ball(int x, int y, int sidelength, int speed, int angle) {
	this->x = x;
	this->y = y;
	this->sidelength = sidelength;
	this->speed = speed;
	this->angle = angle;
}

void Ball::move() {
	double new_x = cos((double) (angle * 3.1415 / 180)) * speed;
	double new_y = sin((double) (angle * 3.1415 / 180)) * speed;
	x += (int) new_x;
	y += (int) new_y;
}


void Ball::draw(SDL_Renderer* renderer) {
	drawRect(renderer, createRect(x, y, sidelength, sidelength), 255, 255, 255);
}
