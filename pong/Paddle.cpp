#include "Paddle.h"
#include "graphics.h"


Paddle::Paddle(int x, int y, int width, int height, int boundingHeight) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->boundingHeight = boundingHeight;
}

void Paddle::move(bool keys[2]) {
	if (keys[0])
		y -= speed;
	if (keys[1])
		y += speed;

	if (y < 0)
		y = 0;
	if (y + height > boundingHeight)
		y = boundingHeight - height;
}

void Paddle::draw(SDL_Surface* screenSurface) {
	drawRect(screenSurface, createRect(x, y, width, height), colour[0], colour[1], colour[2]);
}
