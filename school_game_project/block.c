#include "block.h"

#include <SDL.h>

#include "game.h"
#include "board.h"

extern const struct game game;
extern const struct board board;

#define WIDTH_RATIO (0.2f)
#define HEIGHT_RATIO (0.9f)

#define X_OFFSET_RATIO (WIDTH_RATIO * 2.f)
#define Y_OFFSET_RATIO (0.1f)

void block_render(struct block block)
{
	double angle = block.orientation == BLOCK_ORIENTATION_LEFT_TO_RIGHT ? -45.l : -45.l;
	SDL_RenderCopyEx(
		game.renderer,
		board.block_sprite->texture,
		NULL,
		&(SDL_Rect){
			.x = block.x + (int)board.sprite_dimensions.width * X_OFFSET_RATIO,
			.y = block.y + (int)board.sprite_dimensions.height * Y_OFFSET_RATIO,
			.w = (int)board.sprite_dimensions.width * WIDTH_RATIO,
			.h = (int)board.sprite_dimensions.height * HEIGHT_RATIO,
		},
		angle,
		NULL,
		SDL_FLIP_NONE
	);
}

void block_check_collision(struct block block)
{

}
