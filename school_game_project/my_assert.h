#ifndef MY_ASSSERT_H_
#define MY_ASSERT_H_

#define my_assert(expression)\
if(!expression)\
{\
	SDL_Log("failed to assert (" #expression ")\n\tSDL_Error: %s\n", SDL_GetError());\
}\
(void)0

#endif 

