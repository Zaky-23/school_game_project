#include "sprite.h"

#include <stdlib.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>

#include "game.h"

const extern struct game game;

sprite_t sprite_load(const char *path)
{
    SDL_Surface *surface = IMG_Load(path);
    if (!surface)
    {
        SDL_Log("failed to load surface (%s)\n\tImage_Error: %s", path, IMG_GetError());
        abort();
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(
        game.renderer,
        surface);
    
    SDL_FreeSurface(surface);

    if (!texture)
    {
        SDL_Log("failed to create texture (%s)\n\tImage_Error: %s", path, IMG_GetError());
        abort();
    }

    return (sprite_t) {
        .texture = texture,
        .width = surface->w,
        .height = surface->h
    };
}

void sprite_destroy(sprite_t sprites[], unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        SDL_DestroyTexture(sprites[i].texture);
    }
}
