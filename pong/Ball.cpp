#include "Ball.h"
#include <stdio.h>

Ball::Ball(double x, double y, int sidelength, double speed) {
	this->x = x;
	this->y = y;
	this->sidelength = sidelength;
	this->initialSpeed = speed;
	this->speed = speed;
	this->gone = false;
	initAngle();
}

void Ball::initAngle() {
	angle = randint(110, 250);
	if (randint(0, 1) == 0)
		angle += 180;
	angle %= 360;
}

void Ball::speedUp() {
	speed += 0.01;
}

void Ball::horizontal_bounce() {
	angle = (540 - angle) % 360;
	speedUp();
}

void Ball::vertical_bounce() {
	angle = (360 - angle) % 360;
	speedUp();
}

void Ball::reset() {
	x = 640 / 2;
	y = 480 / 2;
	initAngle();
	gone = false;
	speed = initialSpeed;
}

int Ball::handle_collision(Paddle* paddle1, Paddle* paddle2, int bounding_width) {
	if (x < paddle1->getX() + paddle1->getWidth() &&
			y >= paddle1->getY() - sidelength &&
			y <= paddle1->getY() + paddle1->getHeight() &&
			!gone) {
		x = paddle1->getX() + paddle1->getWidth();
		horizontal_bounce();
	}

	if (x + sidelength > paddle2->getX() &&
			y >= paddle2->getY() - sidelength &&
			y <= paddle2->getY() + paddle2->getHeight() &&
			!gone) {
		x = paddle2->getX() - sidelength;
		horizontal_bounce();
	}

	if (x < paddle1->getX() + paddle1->getWidth() || x + sidelength > paddle2->getX())
		gone = true;

	if (x < -sidelength) {  // player 2 point
		reset();
		return 1;
	}

	if (x > bounding_width) {  // player 1 point
		reset();
		return 0;
	}
	return -1;
}

void Ball::move(int bounding_height) {
	x += cos((double) (angle * 3.1415 / 180)) * speed;
	y += sin((double) (angle * 3.1415 / 180)) * speed;

	// vertical
	if (y < 0) {
		y = 0;
		vertical_bounce();
	}
	if (y - sidelength > bounding_height) {
		y = bounding_height - sidelength;
		vertical_bounce();
	}
}


void Ball::draw(SDL_Renderer* renderer) {
	drawRect(renderer, createRect((int) x, (int) y, sidelength, sidelength), 255, 255, 255);
}

int Ball::getY() {
	return y;
}
