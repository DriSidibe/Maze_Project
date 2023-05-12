#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


// windows parameters
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_TITLE "MAZE"

// the defaut height and weight of the composit cube of the walls
#define WALL_DEFAULT_BRICK_SIZE 64

// field of view
#define FOV 60 

// player default setting
#define PLAYER_DEFAULT_ANGLE_FACED 45
#define PLAYER_DEFAULT_X_POS 0
#define  PLAYER_DEFAULT_Y_POS 0

// projection plan setting
#define PROJECTION_PLAN_DEFAULT_WIDE 320
#define PROJECTION_PLAN_DEFAULT_HIGHT = 100
#define PROJECTION_PLAN_DEFAULT_CENTER_X (PROJECTION_PLAN_DEFAULT_WIDE / 2)
#define PROJECTION_PLAN_DEFAULT_CENTER_Y (PROJECTION_PLAN_DEFAULT_HIGHT / 2)
#define DISTANCE_TO_THE_PROJECTION_PALN (PROJECTION_PLAN_DEFAULT_WIDE / tan(FOV))
#define ANGLE_BETWEEN_SUBSEQUENCE_RAYS (FOV / PROJECTIOn_PLAN_DEFAULT_WIDE)

// the center of the game ground
#define WORLD_CENTER_X 0
#define WORLD_CENTER_y 0

#include <math.h>

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
