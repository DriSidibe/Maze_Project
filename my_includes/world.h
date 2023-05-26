#ifndef __WORL_H__
#define __WORLD_H__

#include <SDL.h>
#include <stdio.h>
#include "../my_includes/player.h"

int run(int argc, char *argv[]);
void DrawCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius);
void get_right_collide_wall();
void get_right_collide_wall();
void set_player_grid_pos();
void get_direction_ray_director_vector();
void calculate_current_ray_equation();
void get_current_ray_director_vector();
void drawing_caluclation(SDL_Renderer *renderer);
void set_player_collision();
void calculate_current_ray_angles(int direction);
void get_right_collide_vertical_wall();
void get_right_collide_horizontal_wall();

#endif
