#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// frame rate (1000ms / 60fps)
int SCREEN_TICKS_PER_FRAME = 100 / 60;

// initialize SDL
int init();

// free memory
void close();

// rendering window
SDL_Window* window = NULL;

// window renderer
SDL_Renderer* renderer = NULL;

int init()
{
	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return 0;
	}
	else {
		// create window
		window = SDL_CreateWindow("SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return 0;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return 0;
			}
			else {
				// set background to black
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
		}
	}

	return 1;
}

void close()
{
	// destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	int frameTime = 0;

	// init random generator (does not work in global space)
	srand((unsigned)time(NULL));

	// main loop quit
	int quit = 0;

	// event handler
	SDL_Event e;

	// dot
	const int dot_width = 5;
	const int dot_height = 5;

	SDL_Rect dot = {
		SCREEN_WIDTH / 2,	// x-pos
		SCREEN_HEIGHT / 2,	// y-pos
		dot_width,			// width
		dot_height			// height
	};

	// start up SDL
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else
	{
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				// user click the x button
				if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = 1;
				}
			}

			frameTime++;
			printf("%d\n", frameTime);
			if (frameTime > SCREEN_TICKS_PER_FRAME)
			{
				frameTime = 0;

				// change dot position
				switch (rand() % 5) {
				case 0:
					dot.x += dot_width*3;
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					break;

				case 1:
					dot.y += dot_height*3;
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					break;

				case 2:
					dot.x -= dot_width*3;
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					break;

				case 3:
					dot.y -= dot_height*3;
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					break;
				}

				//SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255);
			}

			// clear screen
			//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			//SDL_RenderClear(renderer);		

			// draw dot white
			//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &dot);

			// update screen
			SDL_RenderPresent(renderer);
		}
	}

	close();

	return 0;
}