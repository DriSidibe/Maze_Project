#ifndef __GROUND_H__
#define __GROUND_H__

#include "constants.h"

/**
 * struct brick - the ground structure
 *
 *  Description: Longer description
 */
typedef struct brick{
	int width = WALL_DEFAULT_BRICK_SIZE;
	int height = WALL_DEFAULT_BRICK_SIZE;
	int x;
	int y;
}
brick;

#endif
