#include "game.h"

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "board.h"
#include "my_assert.h"
#include "sprite.h"

#define WINDOW_TITLE "Jeu De Memoire"
#define INITIAL_WINDOW_WIDTH (800)
#define INITIAL_WINDOW_HEIGHT (600)
#define SDL_FLAGS (SDL_INIT_VIDEO)
#define IMAGE_FLAGS (IMG_INIT_PNG)
#define WINDOW_FLAGS (SDL_WINDOW_SHOWN)
#define RENDERER_FLAGS (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)

struct game game;

enum {
	SPRITE_BACKGROUND = 0,
	SPRITE_BALL = 1,
	SPRITE_BLOCK = 2,
	SPRITE_HOLE=3,
	SPRITE_MAX
};
static char *sprite_paths[SPRITE_MAX] = {
	"assets/background_brown.png",
	"assets/ball_red_large.png",
	"assets/block_narrow.png",
	"assets/hole.png",
};
static sprite_t sprites[SPRITE_MAX] = { 0 };

static void game_load_assets(void);
static void game_poll_events(void);
static void game_update(void);
static void game_render(void);
static int game_input_handler_callback(void *userdata, SDL_Event *event);

void game_init(void)
{
	if (SDL_Init(SDL_FLAGS) < 0)
	{
		SDL_Log("could not initialize SDL\n\tSDL_Error: %s\n", SDL_GetError());
		abort();
	}

	if (!(IMG_Init(IMAGE_FLAGS) & IMAGE_FLAGS))
	{
		SDL_Log("could not initialize SDL_image\n\tImage_Error: %s\n", IMG_GetError());
		abort();
	}

	SDL_Window *window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		INITIAL_WINDOW_WIDTH,
		INITIAL_WINDOW_HEIGHT,
		WINDOW_FLAGS);
	my_assert(window);

	SDL_Renderer *renderer = SDL_CreateRenderer(
		window,
		-1,
		RENDERER_FLAGS);
	my_assert(renderer);

	SDL_SetRenderDrawColor(renderer, 0xB3, 0xA4, 0x92, 255);

	SDL_AddEventWatch(game_input_handler_callback, NULL);

	game = (struct game){
		.running = SDL_TRUE,
		.window = window,
		.renderer = renderer,
		.event = 0,
		.display_dimensions = {
			.width = INITIAL_WINDOW_WIDTH,
			.height = INITIAL_WINDOW_HEIGHT,
		},
		.render_scale = SDL_floorf((float)INITIAL_WINDOW_WIDTH / (float)INITIAL_WINDOW_HEIGHT * 10.f) / 10.f
	};

	game_load_assets();

	board_init(
		&sprites[SPRITE_BACKGROUND], 
		&sprites[SPRITE_BLOCK], 
		&sprites[SPRITE_HOLE]
	);
}

void game_run(void)
{
	while (game.running)
	{
		game_poll_events();
		game_update();
		game_render();
	}
}

void game_close(void)
{
	SDL_DestroyRenderer(game.renderer);
	game.renderer = NULL;
	SDL_DestroyWindow(game.window);
	game.window = NULL;
}

static void game_load_assets(void)
{
	sprites[SPRITE_BACKGROUND] = sprite_load(sprite_paths[SPRITE_BACKGROUND]);
	sprites[SPRITE_BALL] = sprite_load(sprite_paths[SPRITE_BALL]);
	sprites[SPRITE_BLOCK] = sprite_load(sprite_paths[SPRITE_BLOCK]);
	sprites[SPRITE_HOLE] = sprite_load(sprite_paths[SPRITE_HOLE]);
}

static void game_poll_events(void)
{
	while (SDL_PollEvent(&game.event));
}

static void game_render(void)
{
	SDL_RenderClear(game.renderer);
	board_render();
	SDL_RenderPresent(game.renderer);
}

static void game_update(void)
{
}

static int game_input_handler_callback(void *userdata, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
	{
		game.running = SDL_FALSE;
		return 0;
	}

	return 0;
}
