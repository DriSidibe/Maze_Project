#ifndef __GROUND_H__
#define __GROUND_H__

#include "constants.h"

/**
 * struct brick - the ground structure
 *
 *  Description: Longer description
 */
typedef struct brick{
	int width = wall_default_brick_size;
	int height = wall_default_brick_size;
	int x;
	int y;
}
brick;

#endif
