#ifndef __GROUND_H__
#define __GROUND_H__

#include "constants.h"

/**
 * struct ground - the ground structure
 *
 *  Description: Longer description
 */
typedef struct ground{
	int width;
	int height;
	int wall_bricks_size = WALL_DEFAULT_BRICKS_SIZE;
}
ground;

#endif
