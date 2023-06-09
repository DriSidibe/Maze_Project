#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define PI 3.14159265358979323846

#include <math.h>


int map_width = 640;
int map_height = 640;

// windows parameters
int screen_width = 640;
char *window_title = "MAZE";
float space_between_map = 0;

// the defaut height and weight of the composit cube of the walls
int wall_default_brick_size = 64;

// field of view
int fov = 60;

// player default setting
int player_defaut_angle_faced = 45;
int player_default_x_pos = 180;
int player_default_y_pos = 80;
int player_default_x_grid_pos = 1;
int player_default_y_grid_pos = 1;
int player_default_step = 10;
float player_default_fov = PI/3;
float player_default_pov = 45;

// projection plan setting
int projection_plan_default_wide = 320;
int projection_plan_default_height = 200;

//the map mask
int map_row_count = 10;
int map_column_count = 10;
int map_mask[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };

#endif