#ifndef BOARD_H_
#define BOARD_H_

#include "sprite.h"
#include "vector.h"

struct board
{
	unsigned short level;
	sprite_t *tile_sprite;
	sprite_t *block_sprite;
	sprite_t *hole_sprite;
	struct 
	{
		float width;
		float height;
	} sprite_dimensions;
	struct
	{
		int x0;
		int y0;
		int width;
		int height;
	} tiles_render_area;
};

void board_init(sprite_t *tile, sprite_t *block, sprite_t *hole);
void board_render(void);
void board_increase_level(void);
void board_descrease_level(void);
void board_enable_blocks(void);
void board_disable_blocks(void);

#endif