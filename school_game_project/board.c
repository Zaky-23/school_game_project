#include "board.h"

#include <SDL.h>

#include "block.h"
#include "game.h"
#include "sprite.h"

#define BOARD_STARTING_LEVEL (4)
#define BOARD_RENDER_WIDTH_OFFSET_RATIO (1.f/8.75f)
#define BOARD_RENDER_HEIGHT_OFFSET_RATIO (1.f/8.f)
#define BOARD_RENDER_AREA_RATIO_REL_TO_WINDOW_WIDTH (0.7f)
#define BOARD_RENDER_AREA_RATIO_REL_TO_WINDOW_HEIGHT (0.7f)

const extern struct game game;
struct board board = { 0 };
static int render_blocks = 1;

void board_init(sprite_t *tile, sprite_t *block, sprite_t *hole)
{
	board = (struct board){
		.level = BOARD_STARTING_LEVEL,
		.tile_sprite = tile,
		.block_sprite = block,
		.hole_sprite = hole,
		.sprite_dimensions = {
			.width = game.display_dimensions.width * BOARD_RENDER_AREA_RATIO_REL_TO_WINDOW_WIDTH / BOARD_STARTING_LEVEL,
			.height = game.display_dimensions.height * BOARD_RENDER_AREA_RATIO_REL_TO_WINDOW_HEIGHT / BOARD_STARTING_LEVEL
		},
		.tiles_render_area = { 
			.x0 = game.display_dimensions.width * game.render_scale * BOARD_RENDER_WIDTH_OFFSET_RATIO,
			.y0 = game.display_dimensions.height * game.render_scale * BOARD_RENDER_HEIGHT_OFFSET_RATIO,
			.width = game.display_dimensions.width * BOARD_RENDER_AREA_RATIO_REL_TO_WINDOW_WIDTH,
			.height = game.display_dimensions.height * BOARD_RENDER_AREA_RATIO_REL_TO_WINDOW_HEIGHT
		}
	};
}

static void board_render_holes(void)
{
	int level = (board.level % 2 == 0 ? board.level : board.level + 1);

	int width = board.sprite_dimensions.width * 0.35f;
	int height = board.sprite_dimensions.height * 0.35f;

	int x_offset = width * 0.5f;
	int x_offset_2 = x_offset * 2;
	int y_offset = height * 0.5f;
	int y_offset_2 = y_offset * 2;

	int x_max = (board.level + 1) * board.sprite_dimensions.width;
	int y_max = (board.level + 1) * board.sprite_dimensions.height;

	for (unsigned short x = 1; x <= level / 2; x++)
	{
		int x0 = board.sprite_dimensions.width * x + x_offset;
		for (unsigned short y = 1; y <= level / 2; y++)
		{
			int y0 = board.sprite_dimensions.height * y + y_offset;

			SDL_RenderCopy(
				game.renderer,
				board.hole_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.x = x0,
					.y = y_offset,
					.w = width,
					.h = height
			});

			SDL_RenderCopy(
				game.renderer,
				board.hole_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.x = x_offset,
					.y = y0,
					.w = width,
					.h = height
			});

			SDL_RenderCopy(
				game.renderer,
				board.hole_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.x = x_max - x0 + x_offset_2,
					.y = y_offset,
					.w = width,
					.h = height
			});

			SDL_RenderCopy(
				game.renderer,
				board.hole_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.x = x_offset,
					.y = y_max - y0 + y_offset_2,
					.w = width,
					.h = height
			});

			SDL_RenderCopy(
				game.renderer,
				board.hole_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.x = x_max + x_offset,
					.y = y0,
					.w = width,
					.h = height
			});

			SDL_RenderCopy(
				game.renderer,
				board.hole_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.x = x_max + x_offset,
					.y = y_max - y0 + 2 * y_offset,
					.w = width,
					.h = height
			});

			SDL_RenderCopy(
				game.renderer,
				board.hole_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.x = x_max - x0 + x_offset_2,
					.y = y_max + y_offset,
					.w = width,
					.h = height
			});

			SDL_RenderCopy(
				game.renderer,
				board.hole_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.x = x0,
					.y = y_max + y_offset,
					.w = width,
					.h = height
			});
		}
	}
}

static void board_render_tiles(void)
{
	for (unsigned short x = 0; x < board.level; x++)
	{
		int x0 = board.tiles_render_area.x0 + x * board.sprite_dimensions.width;
		//int x0 = x * w;
		//if (x0 % 2 != 0) x0 += 1;
		for (unsigned short y = 0; y < board.level; y++)
		{
			//int y0 = y * h;
			//if (y0 % 2 != 0) y0 += 1;
			SDL_RenderCopy(
				game.renderer,
				board.tile_sprite->texture,
				NULL,
				&(SDL_Rect) {
					.w = board.sprite_dimensions.width,
					.h = board.sprite_dimensions.height,
					.x = x0,
					.y = board.tiles_render_area.y0 + y * board.sprite_dimensions.height
			});
		}
	}
}

static void board_render_blocks(void)
{
	if (!render_blocks) return;
	for (unsigned short x = 0; x < board.level; x++)
	{
		int x0 = board.tiles_render_area.x0 + x * board.sprite_dimensions.width;
		for (unsigned short y = 0; y < board.level; y++)
		{
			block_render((struct block) { 
				.orientation = BLOCK_ORIENTATION_LEFT_TO_RIGHT, 
					.x = x0, 
					.y = board.tiles_render_area.y0 + y * board.sprite_dimensions.height
			});
		}
	}
}

void board_render(void)
{
	board_render_holes();
	board_render_tiles();
	board_render_blocks();
}

void board_increase_level(void)
{
	board.level += 1;
	board.sprite_dimensions.width = board.tiles_render_area.width / board.level;
	board.sprite_dimensions.height = board.tiles_render_area.height / board.level;
}

void board_descrease_level(void)
{
	board.level -= 1;
	board.sprite_dimensions.width = board.tiles_render_area.width / board.level;
	board.sprite_dimensions.height = board.tiles_render_area.height / board.level;
}

void board_enable_blocks(void)
{
	render_blocks = 1;
}

void board_disable_blocks(void)
{
	render_blocks = 0;
}
