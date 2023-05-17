#ifndef __GLOBAL_H__
#define __GLOBAL_H__

double current_ray_equ_a, current_ray_equ_b;
int mouse_pos_x, mouse_pos_y;
double step_angle;
double current_ray_x, current_ray_y;
double orientation_ray_x, orientation_ray_y;
double orientation_ray_director_x, orientation_ray_director_y;
double current_ray_director_vector_x, current_ray_director_vector_y;
double current_horizontal_collision_point_x, current_horizontal_collision_point_y;
double current_vertical_collision_point_x, current_vertical_collision_point_y;
double first_horizontal_collided_line_y, first_vertical_collided_line_x;
double collided_point_x, collided_point_y;
double current_horizontal_vector_size, current_vertical_vector_size;
double total_angle_count = 0;
double elementary_angle;
double k;

#endif
