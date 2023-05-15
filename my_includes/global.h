#ifndef __GLOBAL_H__
#define __GLOBAL_H__

float current_ray_equ_a, current_ray_equ_b;
float straight_vect_x, straight_vect_y;
float ray_x, ray_y;
int mouse_pos_x, mouse_pos_y;
float mouse_pos_x_old;
float mouse_pos_y_old;
float vert_collide_point_x, vert_collide_point_y;
float vert_collide_point_size, horiz_collide_point_size;
float horiz_collide_point_x, horiz_collide_point_y;
float step_angle;
float current_ray_point_x, current_ray_point_y;
int current_first_horiz_point_y, current_first_vert_point_x;
 float current_first_horiz_point_x, current_first_vert_point_y;
int next_horiz_line_x, next_horiz_line_y;
int is_touch_wall = 1;
float k;

#endif
