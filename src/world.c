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
    player->pos_x_grid = player_default_x_grid_pos;
    player->pos_y_grid = player_default_y_grid_pos;
    mouse_pos_x = 0;
    mouse_pos_y = 0;
    player->fov = player_default_fov;
    player->pov = player_default_pov;
    step_angle = fov/projection_plan_default_wide;

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
                            k = 1/(sqrt(pow(ray_x, 2)+pow(ray_y, 2))/player_default_step);
                            if (k < 1)
                            {
                                player->pos_x += k*ray_x;
                                player->pos_y += k*ray_y;
                                set_player_grid_pos(player);  
                            }
                            break;
                    }
                    break;
            }


			if (isOpen)
            {
                if(0 != SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255))
                {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
                    SDL_Quit(); 
                    return EXIT_FAILURE;
                }
                SDL_RenderClear( renderer );

                // set ray end position
                ray_x = mouse_pos_x - player->pos_x;
                ray_y = mouse_pos_y - player->pos_y;

                mouse_pos_x_old = mouse_pos_x;
                mouse_pos_y_old = mouse_pos_y;
                SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);

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
                player->pov = (acosf((ray_x)/(sqrt(pow(ray_x, 2)+pow(ray_y, 2))))*180)/PI;

                //draw player
                SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
                DrawCircle(renderer, player->pos_x, player->pos_y, 5);

                //draw orientation straight
                //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                //SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, mouse_pos_x, mouse_pos_y);

                //draw throwed rays

                    //search frist horzontal collide pointe
                current_ray_point_x = mouse_pos_x;
                current_ray_point_y = mouse_pos_y;
                get_ray_director_vector();
                calculate_ray_equation(); 
                if (straight_vect_y < 0)
                {
                    get_horiz_collide_wall(-1);
                }
                else
                {
                    get_horiz_collide_wall(1);
                }

                if (straight_vect_x < 0)
                {
                    get_vert_collide_wall(-1);
                }
                else
                {
                    get_vert_collide_wall(1);
                }
                vert_collide_point_size = sqrtf(powf(vert_collide_point_x, 2) + powf(vert_collide_point_y, 2));
                horiz_collide_point_size = sqrtf(powf(horiz_collide_point_x, 2) + powf(horiz_collide_point_y, 2));
                current_ray_point_x = vert_collide_point_size < horiz_collide_point_size ? vert_collide_point_x : horiz_collide_point_x;
                current_ray_point_y = vert_collide_point_size < horiz_collide_point_size ? vert_collide_point_y : horiz_collide_point_y;
                //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                //SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, current_ray_point_x, current_ray_point_y);

                SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                DrawCircle(renderer, current_first_horiz_point_x, current_first_horiz_point_y, 5);
                SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, current_first_horiz_point_x, current_first_horiz_point_y);

                //SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
                //DrawCircle(renderer, current_first_vert_point_x, current_first_vert_point_y, 5);
                
                

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

void get_horiz_collide_wall(int direct)
{

    get_first_horiz_oollide_point(direct);
    current_first_horiz_point_y = next_horiz_line_y;
    current_first_horiz_point_x = (current_first_horiz_point_y - current_ray_equ_b)/current_ray_equ_a;

    int x = floor(current_first_horiz_point_x/wall_default_brick_size);
    int y_bottom = current_first_horiz_point_y/wall_default_brick_size;
    int y_top = current_first_horiz_point_y/wall_default_brick_size - 1;

    do
    {
        if (direct == 1)
        {
            //printf("(%d, %d) top hor_y: %d\n", x, y_bottom, current_first_horiz_point_y);
            printf("%d\n", map_mask[x][y_bottom]);
            if (map_mask[x][y_bottom] == 1)
            {
                is_touch_wall = 0;
            }
            else
            {
                current_first_horiz_point_y += wall_default_brick_size;
                current_first_horiz_point_x = (current_first_horiz_point_y - current_ray_equ_b)/current_ray_equ_a;
            }
            
        }
        else
        {
            //printf("(%d, %d) bottom hor_y: %d\n", x, y_top, current_first_horiz_point_y);
            if (map_mask[x][y_top] == 1)
            {
                is_touch_wall = 0;
            }
            else
            {
                current_first_horiz_point_y -= wall_default_brick_size;
                current_first_horiz_point_x = (current_first_horiz_point_y - current_ray_equ_b)/current_ray_equ_a;
            }
        }

    } while (is_horiz_out_of_bound() == 1 || is_touch_wall == 1);
    
}

void get_vert_collide_wall(int direct)
{
    int next_vert_line_x;

    if (direct == 1)
    {
        next_vert_line_x = player->pos_x_grid*64 + 64;
    }
    else
    {
        next_vert_line_x = player->pos_x_grid*64;
    }
    current_first_vert_point_x = next_vert_line_x;
    current_first_vert_point_y = current_ray_equ_b + current_first_vert_point_x*current_ray_equ_a;
}

void set_player_grid_pos()
{
    float ratio_x = player->pos_x/64;
    float ratio_y = player->pos_y/64;

    player->pos_x_grid = floorf(ratio_x);
    player->pos_y_grid = floorf(ratio_y);
}

void calculate_ray_equation()
{
    current_ray_equ_a = (player->pos_y - current_ray_point_y)/(player->pos_x - current_ray_point_x);
    current_ray_equ_b = player->pos_y - current_ray_equ_a*player->pos_x;
}

void get_ray_director_vector()
{
    straight_vect_x = current_ray_point_x - player->pos_x;
    straight_vect_y = current_ray_point_y - player->pos_y;
}

int is_horiz_out_of_bound()
{
    int x_right, x_left;
    printf("%d", current_first_horiz_point_x);
    x_right = map_width + space_between_map - wall_default_brick_size;
    x_left = space_between_map + wall_default_brick_size;

    if (current_first_horiz_point_y == wall_default_brick_size + space_between_map || current_first_horiz_point_y == map_height + space_between_map - wall_default_brick_size)
        return 0;
    if (current_first_horiz_point_x > x_right)
    {
        current_first_horiz_point_x = x_right;
        current_first_vert_point_y = current_ray_equ_b + current_first_horiz_point_x*current_ray_equ_a;
        return 0;
    }
    if (current_first_horiz_point_x < x_left)
    {
        current_first_horiz_point_x = x_left;
        current_first_vert_point_y = current_ray_equ_b + current_first_horiz_point_x*current_ray_equ_a;
        return 0;
    }
    return 1;
}

int is_vert_out_of_bound()
{
    if (current_first_vert_point_x <= 0 || current_first_vert_point_x > map_width + space_between_map)
        return 0;
    

    return 1;
}

void get_first_horiz_oollide_point(int direct)
{
    if (direct == 1)
    {
        next_horiz_line_y = player->pos_y_grid*64 + 64;        
    }
    else
    {
        next_horiz_line_y = player->pos_y_grid*64;
    }
}

void get_first_vert_collide_point(int direct)
{
    if (direct == 1)
    {
        next_vert_line_x = player->pos_y_grid*64 + 64;        
    }
    else
    {
        next_vert_line_x = player->pos_y_grid*64;
    }
}