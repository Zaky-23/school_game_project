#ifndef BLOCK_H_
#define BLOCK_H_

enum block_orienation
{
	BLOCK_ORIENTATION_RIGHT_TO_LEFT = 0,
	BLOCK_ORIENTATION_LEFT_TO_RIGHT = 1,
	BLOCK_ORIENTATION_MAX
};

typedef struct block 
{
	enum block_orientation orientation;
	struct position
	{
		int x;
		int y;
	};
} block_t;

void block_render(struct block block);
void block_check_collision(struct block block);

#endif