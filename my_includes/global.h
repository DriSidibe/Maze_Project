#ifndef __GLOBAL_H__
#define __GLOBAL_H__

float current_ray_equ_a, current_ray_equ_b;
int mouse_pos_x, mouse_pos_y;
float step_angle;
float current_ray_x, current_ray_y;
float orientation_ray_x, orientation_ray_y;
float orientation_ray_director_x, orientation_ray_director_y;
float current_ray_director_vector_x, current_ray_director_vector_y;
float current_horizontal_collision_point_x, current_horizontal_collision_point_y;
float current_vertical_collision_point_x, current_vertical_collision_point_y;
float first_horizontal_collided_line_y, first_vertical_collided_line_x;
int is_touch_wall = 1;
float k;

#endif
