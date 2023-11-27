#include "SDL_gpu.h"
#include <iostream>

const int WIDTH = 640;
const int HEIGHT = 480;


void update_color_shader(float r, float g, float b, float a, int color_loc) {
    float fcolor[4] = {r, g, b, a};
    GPU_SetUniformfv(color_loc, 4, 1, fcolor);
}


int main(int argc, char *argv[]) {
	// https://github.com/grimfang4/sdl-gpu/blob/master/tests/renderer/main.c#L34 line 57 for changing window title
	GPU_Target* screen = GPU_Init(WIDTH, HEIGHT, GPU_DEFAULT_INIT_FLAGS);

	if (screen == NULL)
		return 3;

	Uint32 fragment_shader = GPU_LoadShader(GPU_FRAGMENT_SHADER, (const char*) "shader.frag");
	Uint32 vertex_shader = GPU_LoadShader(GPU_VERTEX_SHADER, (const char*) "shader.vert");

	printf("%d\n", fragment_shader);
	printf("%d\n", vertex_shader);

	Uint32 color_shader = GPU_LinkShaders(fragment_shader, vertex_shader);

	GPU_ShaderBlock block = GPU_LoadShaderBlock(color_shader, "gpu_Vertex", "gpu_TexCoord", "gpu_Color", "gpu_ModelViewProjectionMatrix");
	GPU_ActivateShaderProgram(color_shader, &block);
	int location = GPU_GetUniformLocation(color_shader, "myColor");


	SDL_Event event;
	float t;
	bool run = true;
	while (run) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				run = false;
		}

		t = SDL_GetTicks()/1000.0f;

		//GPU_ClearRGBA(screen, 240, 240, 240, 255);
		//GPU_RectangleFilled(screen, 10, 10, 100, 20, GPU_MakeColor(200, 20, 23, 255));

		GPU_ActivateShaderProgram(color_shader, &block);
        update_color_shader(1.0f, 1.0f, 1.0f, 1.0f, location);

        //GPU_ActivateShaderProgram(0, NULL);

		GPU_Flip(screen);

	}

	GPU_Quit();

	return 0;
}