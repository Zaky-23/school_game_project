#define SDL_MAIN_HANDLED
#include "game.h"

int main(int argc, char **argv)
{
	game_init();
	game_run();
	game_close();
	return 0;
}