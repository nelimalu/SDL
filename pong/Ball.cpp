#include "Ball.h"
#include <stdio.h>

Ball::Ball(double x, double y, int sidelength, double speed, int angle) {
	this->x = x;
	this->y = y;
	this->sidelength = sidelength;
	this->speed = speed;
	this->angle = angle;
	this->gone = false;
}

void Ball::horizontal_bounce() {
	angle = (540 - angle) % 360;
}

void Ball::vertical_bounce() {
	angle = (360 - angle) % 360;
}

void Ball::reset() {
	x = 640 / 2;
	y = 480 / 2;
	angle = randint(0, 359);
	gone = false;
}

void Ball::handle_collision(Paddle* paddle1, Paddle* paddle2, int bounding_width) {
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
		printf("PLAYER 2 POINT\n");
	}

	if (x > bounding_width) {  // player 1 point
		reset();
		printf("PLAYER 1 POINT\n");
	}
}

void Ball::move(Paddle* paddle1, Paddle* paddle2, int bounding_width, int bounding_height) {
	x += cos((double) (angle * 3.1415 / 180)) * speed;
	y += sin((double) (angle * 3.1415 / 180)) * speed;

	handle_collision(paddle1, paddle2, bounding_width);

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
