#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>

struct game
{
	SDL_bool running;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	struct dimensions
	{
		int width;
		int height;
	} display_dimensions;
	float render_scale;
};

void game_init(void);
void game_run(void);
void game_close(void);

#endif