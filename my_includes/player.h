#ifndef __PLAYER_H__
#define __PLAYER_H__

/**
 * struct ground - the player structure
 *
 *  Description: Longer description
 */
typedef struct player{
        int pos_x;
        int pos_y;
        int pos_x_grid;
        int pos_y_grid;
        float pov;
        float fov;
}
Player;

#endif
