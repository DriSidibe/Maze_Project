#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../my_includes/constants.h"
#include "../my_includes/world.h"
#include "../my_includes/global.h"


Player *player = NULL;

int run(int argc, char *argv[])
{

    // variables declaration
	SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
	SDL_Event events;
    int isOpen;
    SDL_Rect map = {
        20, 20, map_width, map_height
    };
    
    // variables intialization
    isOpen = 1;
    player = malloc(sizeof(Player));
    player->pos_x = player_default_x_pos;
    player->pos_y = player_default_y_pos;
    mouse_pos_x = 0;
    mouse_pos_y = 0;
    player->fov = player_default_fov;
    player->pov = player_default_pov;
    step_angle = fov/projection_plan_default_wide;
    elementary_angle = player->fov/projection_plan_default_wide;

    //----------------------------------
	





    // sdl intialisations
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
	if (SDL_CreateWindowAndRenderer(map_width + space_between_map*2, map_height + space_between_map*2, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }
    //-----------------------------------------
    











    //main loop
    while (isOpen)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
                case SDL_QUIT:
                    isOpen = 0;
                    free(player);
                    break;
                case SDL_KEYDOWN:
                    switch (events.key.keysym.sym)
                    {
                        case SDLK_a:
                            k = 1/(sqrt(pow(orientation_ray_director_x, 2)+pow(orientation_ray_director_y, 2))/player_default_step);
                            if (k < 1)
                            {
                                player->pos_x += k*orientation_ray_director_x;
                                player->pos_y += k*orientation_ray_director_y;
                            }
                            set_player_collision();
                            break;
                    }
                    break;
            }


			if (isOpen)
            {
                //set player grid poition
                set_player_grid_pos();

                //get mouse position
                SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
                orientation_ray_x = mouse_pos_x;
                orientation_ray_y = mouse_pos_y;

                //set orientation ray director
                get_direction_ray_director_vector();

                if(0 != SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255))
                {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
                    SDL_Quit(); 
                    return EXIT_FAILURE;
                }
                SDL_RenderClear( renderer );


                // drawing area

                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                SDL_RenderFillRect( renderer, &map );

                // draw walls
                for (int i = 0; i < map_width; i++)
                {
                    for (int j = 0; j < map_height; j++)
                    {
                        if (map_mask[i][j] == 1)
                        {
                            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
                            SDL_Rect r = {
                                i*wall_default_brick_size + space_between_map, j*wall_default_brick_size + space_between_map,
                                wall_default_brick_size, wall_default_brick_size
                            };
                            SDL_RenderFillRect( renderer, &r );
                        }
                    }
                }

                //calculate the player pov
                player->pov = (acosf((orientation_ray_director_x)/(sqrt(pow(orientation_ray_director_y, 2)+pow(orientation_ray_director_y, 2))))*180)/PI;

                //draw player
                SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
                DrawCircle(renderer, player->pos_x, player->pos_y, 5);

                /*
                //draw orientation ray
                SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, orientation_ray_x, orientation_ray_y);
                */

                //draw orientation ray director vector
                //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                //SDL_RenderDrawLine(renderer, 0, 0, orientation_ray_director_x, orientation_ray_director_y);
                
                //draw right throwed rays
                current_ray_x = orientation_ray_x;
                current_ray_y = orientation_ray_y;

                //draw on throwed ray
                drawing_caluclation(renderer);

                //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                //DrawCircle(renderer, collided_point_x, collided_point_y, 5);
                //SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                //SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, collided_point_x, collided_point_y);
                //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                //DrawCircle(renderer, current_horizontal_collision_point_x, current_horizontal_collision_point_y, 5);
                //SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
                //DrawCircle(renderer, current_vertical_collision_point_x, current_vertical_collision_point_y, 5);
                //printf("%f\n", current_ray_angle);
                //printf("%f, %f\n", current_horizontal_collision_point_x, current_horizontal_collision_point_y);
                //printf("%f, %f\n", current_vertical_collision_point_x, current_vertical_collision_point_y);

                /*
                do
                {
                    drawing_caluclation(renderer);

                    //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                    //DrawCircle(renderer, collided_point_x, collided_point_y, 5);
                    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                    SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, collided_point_x, collided_point_y);

                    current_ray_x = (orientation_ray_x - player->pos_x)*cos(total_angle_count) - (orientation_ray_y - player->pos_y)*sin(total_angle_count) + player->pos_x;
                    current_ray_y = (orientation_ray_x - player->pos_x)*sin(total_angle_count) + (orientation_ray_y - player->pos_y)*cos(total_angle_count) + player->pos_y;

                    total_angle_count += elementary_angle;

                }while (total_angle_count < player->fov/2);
                total_angle_count = 0;
                */
                

                /*
                //draw left throwed rays
                current_ray_x = orientation_ray_x;
                current_ray_y = orientation_ray_y;

                do
                {
                    drawing_caluclation(renderer);

                    //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                    //DrawCircle(renderer, collided_point_x, collided_point_y, 5);
                    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
                    SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, collided_point_x, collided_point_y);

                    current_ray_x = (orientation_ray_x - player->pos_x)*cos(-total_angle_count) - (orientation_ray_y - player->pos_y)*sin(-total_angle_count) + player->pos_x;
                    current_ray_y = (orientation_ray_x - player->pos_x)*sin(-total_angle_count) + (orientation_ray_y - player->pos_y)*cos(-total_angle_count) + player->pos_y;

                    total_angle_count += elementary_angle;
                    printf("%f\n", total_angle_count);

                }while (total_angle_count < player->fov/2);
                total_angle_count = 0;
                */
                

                //-----------------------------------------









                //render the renderer
                SDL_RenderPresent(renderer);
                if(0 != SDL_RenderClear(renderer))
                {
                        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
                        SDL_Quit(); 
                        return EXIT_FAILURE;
                }
                //-----------------------------------------
            }

    	}
    }
    //-----------------------------------------

    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
	
    return 0;
}











// fonctions
void DrawCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawLine(renderer, centreX, centreY, centreX + x, centreY - y);
        SDL_RenderDrawLine(renderer,centreX, centreY, centreX + x, centreY + y);
        SDL_RenderDrawLine(renderer,centreX, centreY, centreX - x, centreY - y);
        SDL_RenderDrawLine(renderer,centreX, centreY, centreX - x, centreY + y);
        SDL_RenderDrawLine(renderer,centreX, centreY, centreX + y, centreY - x);
        SDL_RenderDrawLine(renderer,centreX, centreY, centreX + y, centreY + x);
        SDL_RenderDrawLine(renderer,centreX, centreY, centreX - y, centreY - x);
        SDL_RenderDrawLine(renderer,centreX, centreY, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void get_horizontal_collide_wall(int direct)
{
    if (direct == 1)
    {
        first_horizontal_collided_line_y = player->pos_y_grid*64 + 64;        
    }
    else
    {
        first_horizontal_collided_line_y = player->pos_y_grid*64;
    }

    current_horizontal_collision_point_y = first_horizontal_collided_line_y;
    current_horizontal_collision_point_x = (current_horizontal_collision_point_y - current_ray_equ_b)/current_ray_equ_a;

    x = floor(current_horizontal_collision_point_x/wall_default_brick_size);
    y_bottom = current_horizontal_collision_point_y/wall_default_brick_size;
    y_top = current_horizontal_collision_point_y/wall_default_brick_size - 1;

    while (1)
    {
        if (direct == 1)
        {
            if (map_mask[x][y_bottom] == 1)
                return;
            else
            {
                current_horizontal_collision_point_y += wall_default_brick_size;
                current_horizontal_collision_point_x = (current_horizontal_collision_point_y - current_ray_equ_b)/current_ray_equ_a;
            }

            
            if (current_horizontal_collision_point_x < space_between_map + wall_default_brick_size || current_horizontal_collision_point_x > map_width + space_between_map - wall_default_brick_size)
            {
                current_horizontal_collision_point_y = map_height + space_between_map - wall_default_brick_size;
                current_horizontal_collision_point_x = (current_horizontal_collision_point_y - current_ray_equ_b)/current_ray_equ_a;
                return;
            }   
            
        }
        else
        {
            if (map_mask[x][y_top] == 1)
                return;
            else
            {
                current_horizontal_collision_point_y -= wall_default_brick_size;
                current_horizontal_collision_point_x = (current_horizontal_collision_point_y - current_ray_equ_b)/current_ray_equ_a;
            }

            
            if (current_horizontal_collision_point_x < space_between_map + wall_default_brick_size || current_horizontal_collision_point_x > map_width + space_between_map - wall_default_brick_size)
            {

                current_horizontal_collision_point_y = space_between_map + wall_default_brick_size;
                current_horizontal_collision_point_x = (current_horizontal_collision_point_y - current_ray_equ_b)/current_ray_equ_a;
                return;
            }
        }

        x = floor(current_horizontal_collision_point_x/wall_default_brick_size);
        y_bottom = current_horizontal_collision_point_y/wall_default_brick_size;
        y_top = current_horizontal_collision_point_y/wall_default_brick_size - 1;
        
    }

}

void get_vertical_collide_wall(int direct)
{
    if (direct == 1)
    {
        first_vertical_collided_line_x = player->pos_x_grid*64 + 64;        
    }
    else
    {
        first_vertical_collided_line_x = player->pos_x_grid*64;
    }

    current_vertical_collision_point_x = first_vertical_collided_line_x;
    current_vertical_collision_point_y = current_ray_equ_b + current_vertical_collision_point_x*current_ray_equ_a;

    y = floor(current_vertical_collision_point_y/wall_default_brick_size);
    x_right = current_vertical_collision_point_x/wall_default_brick_size;
    x_left = current_vertical_collision_point_x/wall_default_brick_size - 1;

    while (1)
    {
        if (direct == 1)
        {
            if (current_ray_director_vector_y > 0)
            {
                if (map_mask[x_right][y] == 0 && floor(current_vertical_collision_point_y/wall_default_brick_size)*wall_default_brick_size+wall_default_brick_size == space_between_map + map_height - wall_default_brick_size)
                {
                    current_vertical_collision_point_y = map_height + space_between_map - wall_default_brick_size;
                    current_vertical_collision_point_x = (current_vertical_collision_point_y - current_ray_equ_b)/current_ray_equ_a;
                    return;
                }
                
            }else
            {
                if (map_mask[x_right][y] == 0 && floor(current_vertical_collision_point_y/wall_default_brick_size)*wall_default_brick_size == space_between_map + wall_default_brick_size)
                {
                    current_vertical_collision_point_y = space_between_map + wall_default_brick_size;
                    current_vertical_collision_point_x = (current_vertical_collision_point_y - current_ray_equ_b)/current_ray_equ_a;
                    return;
                }
            }
            
            if (map_mask[x_right][y] == 1)
                return;
            else
            {
                current_vertical_collision_point_x += wall_default_brick_size;
                current_vertical_collision_point_y = current_ray_equ_b + current_vertical_collision_point_x*current_ray_equ_a;
            }

            
            if (current_vertical_collision_point_y < space_between_map + wall_default_brick_size || current_vertical_collision_point_y > map_height + space_between_map - wall_default_brick_size)
            {
                
                current_vertical_collision_point_x = map_width + space_between_map - wall_default_brick_size;
                current_vertical_collision_point_y = current_ray_equ_b + current_vertical_collision_point_x*current_ray_equ_a;
                return;
            }    
        }
        else
        {
            if (current_ray_director_vector_y > 0)
            {
                if (map_mask[x_left][y] == 0 && floor(current_vertical_collision_point_y/wall_default_brick_size)*wall_default_brick_size+wall_default_brick_size == space_between_map + map_height - wall_default_brick_size)
                {
                    current_vertical_collision_point_y = map_height + space_between_map - wall_default_brick_size;
                    current_vertical_collision_point_x = (current_vertical_collision_point_y - current_ray_equ_b)/current_ray_equ_a;
                    return;
                }
                
            }
            if (map_mask[x_left][y] == 1)
                return;
            else
            {
                current_vertical_collision_point_x -= wall_default_brick_size;
                current_vertical_collision_point_y = current_ray_equ_b + current_vertical_collision_point_x*current_ray_equ_a;
            }

            if (current_vertical_collision_point_y < space_between_map + wall_default_brick_size || current_vertical_collision_point_y > map_height + space_between_map - wall_default_brick_size)
            {
                current_vertical_collision_point_x = space_between_map + wall_default_brick_size;
                current_vertical_collision_point_y = current_ray_equ_b + current_vertical_collision_point_x*current_ray_equ_a;
                return;
            }
        }

        y = floor(current_vertical_collision_point_y/wall_default_brick_size);
        x_right = current_vertical_collision_point_x/wall_default_brick_size;
        x_left = current_vertical_collision_point_x/wall_default_brick_size - 1;
    }

}

void set_player_grid_pos()
{
    float ratio_x = player->pos_x/64;
    float ratio_y = player->pos_y/64;

    player->pos_x_grid = floorf(ratio_x);
    player->pos_y_grid = floorf(ratio_y);
}

void calculate_current_ray_equation()
{
    current_ray_equ_a = (player->pos_y - current_ray_y)/(player->pos_x - current_ray_x);
    current_ray_equ_b = player->pos_y - current_ray_equ_a*player->pos_x;
}

void get_direction_ray_director_vector()
{
    orientation_ray_director_x = orientation_ray_x - player->pos_x;
    orientation_ray_director_y = orientation_ray_y - player->pos_y;
    current_ray_angle = acos((current_ray_director_vector_x)/(sqrt(pow((current_ray_director_vector_x), 2)+pow(current_ray_director_vector_y, 2))))*180/PI;
}

void get_current_ray_director_vector()
{
    current_ray_director_vector_x = current_ray_x - player->pos_x;
    current_ray_director_vector_y = current_ray_y - player->pos_y;
}

void drawing_caluclation(SDL_Renderer *renderer)
{
    get_current_ray_director_vector();
    calculate_current_ray_equation();
                    
    if (current_ray_director_vector_y < 0)
    {
        get_horizontal_collide_wall(-1);
    }
    else
    {
        get_horizontal_collide_wall(1);
    }
                    
    if (current_ray_director_vector_x < 0)
    {
        get_vertical_collide_wall(-1);
    }
    else
    {
        get_vertical_collide_wall(1);
    }
                    
    current_horizontal_vector_size = sqrt(pow((current_horizontal_collision_point_x - player->pos_x), 2)+pow((current_horizontal_collision_point_y - player->pos_y), 2));
    current_vertical_vector_size = sqrt(pow((current_vertical_collision_point_x - player->pos_x), 2)+pow((current_vertical_collision_point_y - player->pos_y), 2));

    collided_point_x = current_horizontal_vector_size < current_vertical_vector_size ? current_horizontal_collision_point_x : current_vertical_collision_point_x;
    collided_point_y = current_horizontal_vector_size < current_vertical_vector_size ? current_horizontal_collision_point_y : current_vertical_collision_point_y;
                    


    /*
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    DrawCircle(renderer, current_horizontal_collision_point_x, current_horizontal_collision_point_y, 5);
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    DrawCircle(renderer, current_vertical_collision_point_x, current_vertical_collision_point_y, 5);
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, current_horizontal_collision_point_x, current_horizontal_collision_point_y);
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, current_vertical_collision_point_x, current_vertical_collision_point_y);
    */

    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    DrawCircle(renderer, current_vertical_collision_point_x, current_vertical_collision_point_y, 5);
    SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, current_vertical_collision_point_x, current_vertical_collision_point_y);
                    
}

void set_player_collision()
{
    if (player->pos_x <= space_between_map + wall_default_brick_size)
        player->pos_x = space_between_map + wall_default_brick_size + player_default_limit;
    else if (player->pos_x >= space_between_map + map_width - wall_default_brick_size)
        player->pos_x = space_between_map + map_width - wall_default_brick_size - player_default_limit;
    
    if (player->pos_y <= space_between_map + wall_default_brick_size)
        player->pos_y = space_between_map + wall_default_brick_size + player_default_limit;
    else if (player->pos_y >= space_between_map + map_width - wall_default_brick_size)
        player->pos_y = space_between_map + map_width - wall_default_brick_size - player_default_limit;
}