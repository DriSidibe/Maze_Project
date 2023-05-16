#ifndef __WORL_H__
#define __WORLD_H__

#include <SDL.h>
#include <stdio.h>
#include "../my_includes/player.h"

int run(int argc, char *argv[]);
void DrawCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius);
void get_horizontal_collide_wall(int direct);
void get_vertical_collide_wall(int direct);
void set_player_grid_pos();
void get_direction_ray_director_vector();
void calculate_current_ray_equation();
void get_current_ray_director_vector();

#endif
