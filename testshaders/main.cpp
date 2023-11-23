#include <SDL.h>
#include <stdio.h>
#include <GL/gl.h>
#include "shader.h"

int WIDTH = 640;
int HEIGHT = 480;
const char* CAPTION = "shadersssssssssss";

int glGetUniformLocation(int program, const char* name);
void glUniform1f(int location, float v0);
void glUniform2f(int location, float v0, float v1);


int main(int argv, char** args) {
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* screen = SDL_CreateWindow(CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	glViewport(0, 0, WIDTH, HEIGHT);

	int p = glCreateProgram();
	shader(shader_fragment, 0x8B30, p);
	glLinkProgram(p);
	glUseProgram(p);
	int timeLocation = glGetUniformLocation(p, "time");
	int resolution = glGetUniformLocation(p, "resolution");
	glUniform2f(resolution, WIDTH, HEIGHT);

	SDL_Event e;
	while (true) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) 
			break;
		float t = SDL_GetTicks() / 500.0;
		glUniform1f(timeLocation, t);
		glRecti(-1, -1, 1, 1);
		SDL_GL_SwapWindow(screen);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	SDL_Quit();

	return 0;
}
