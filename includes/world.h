#ifndef __WORL_H__
#define __WORLD_H__

#include "constants.h"

/**
 * struct world - the ground structure
 *
 *  Description: Longer description
 */
typedef struct world{
	int center_x;
	int center_y;
}
world;

int run_2D();
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
int clearWindow(SDL_Renderer *renderer);

#endif
