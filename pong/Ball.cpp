#include "Ball.h"

Ball::Ball(int x, int y, int sidelength, int speed, float angle) {
	this->x = x;
	this->y = y;
	this->sidelength = sidelength;
	this->speed = speed;
	this->angle = angle;
}

void Ball::move() {
	x += cos(angle * 180 / 3.141592) * speed;
	y += sin(angle * 180 / 3.141592) * speed;

}


void Ball::draw(SDL_Renderer* renderer) {
	drawRect(renderer, createRect(x, y, sidelength, sidelength), 255, 255, 255);
}
