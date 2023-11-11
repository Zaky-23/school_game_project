#ifndef SPRITE_H_
#define SPRITE_H_

#include <stdint.h>
#include <SDL.h>

typedef struct sprite
{
	SDL_Texture *texture;
	int width;
	int height;
} sprite_t;

sprite_t sprite_load(const char *path);
void sprite_destroy(sprite_t sprites[], unsigned int size);

#endif 

