#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <math.h>


int map_width = 640;
int map_height = 512;

// windows parameters
int screen_width = 640;
char *window_title = "MAZE";

// the defaut height and weight of the composit cube of the walls
int wall_default_brick_size = 64;

// field of view
int fov = 60;

// player default setting
int player_defaut_angle_faced = 45;
int player_default_x_pos = 128;
int player_default_y_pos = 128;
int player_default_step = 0.5;

// projection plan setting
int projection_plan_default_wide = 320;
int projection_plan_default_height = 320;

//the map mask
int map_mask[10][12] = {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1}
    };

/**
 * struct POV - the ground structure
 *
 *  Description: Longer description
 */
typedef struct POV{
        int x;
        int Y;
        int faced_angle;
}
POV;

#endif
