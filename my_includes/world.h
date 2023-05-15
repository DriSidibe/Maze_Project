#ifndef __WORL_H__
#define __WORLD_H__

#include <SDL.h>
#include "../my_includes/player.h"

int run(int argc, char **argv[]);
void DrawCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius);
void get_collide_wall(float p_x, float p_y, float x, float y);
void get_first_horiz_line_inter(float f_x, float f_y, float p_x, float p_y);
void set_player_grid_pos(player *p);
void get_ray_director_vector(player *p, float mx, float my, float *s_x, float *s_y);

#endif
