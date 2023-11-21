#include "Paddle.h"


Paddle::Paddle(int x, double y, int width, int height, int boundingHeight) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->boundingHeight = boundingHeight;
}

void Paddle::checkBounds() {
	if (y < 0)
		y = 0;
	if (y + height > boundingHeight)
		y = boundingHeight - height;
}

void Paddle::move(bool keys[2]) {
	if (keys[0])
		y -= speed;
	if (keys[1])
		y += speed;

	checkBounds();
}

void Paddle::move(int ballHeight) {
	if (ballHeight < y + height / 2)  // if ball is above center of paddle
		y -= speed;
	else if (ballHeight > y + height / 2)  // if ball is below center of paddle
		y += speed;

	checkBounds();
}

void Paddle::draw(SDL_Renderer* renderer) {
	drawRect(renderer, createRect(x, (int) y, width, height), colour[0], colour[1], colour[2]);
}

int Paddle::getX() {
	return x;
}

int Paddle::getY() {
	return y;
}

int Paddle::getWidth() {
	return width;
}

int Paddle::getHeight() {
	return height;
}
