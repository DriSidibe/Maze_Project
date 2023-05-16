#ifndef __WORL_H__
#define __WORLD_H__

#include <SDL.h>
#include <stdio.h>
#include "../my_includes/player.h"

int run(int argc, char *argv[]);
void DrawCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius);
void get_vert_collide_wall(int direct);
void get_horiz_collide_wall(int direct);
void set_player_grid_pos();
void get_ray_director_vector();
void calculate_ray_equation();
int is_horiz_out_of_bound();
int is_vert_out_of_bound();
void get_first_horiz_oollide_point(int direct);
void get_first_vert_collide_point(int direct);

#endif
