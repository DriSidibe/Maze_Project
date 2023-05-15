#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../my_includes/constants.h"
#include "../my_includes/world.h"



int run(int argc, char **argv[])
{

    // variables declaration
	SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
	SDL_Event events;
    int isOpen;
    player *player = NULL;
    int ray_x;
    int ray_y;
    float k;
    int mouse_pos_x;
    int mouse_pos_y;
    float mouse_pos_x_old;
    float mouse_pos_y_old;
    float collide_point_x, collide_point_y;
    float step_angle;
    float tmp_angle;
    float straight_vect_x;
    float straight_vect_y;
    SDL_Rect map = {
        20, 20, map_width, map_height
    };
    
    // variables intialization
    isOpen = 1;
    player = malloc(sizeof(player));
    player->pos_x = player_default_x_pos;
    player->pos_y = player_default_y_pos;
    mouse_pos_x = 0;
    mouse_pos_y = 0;
    tmp_angle = 0;
    player->fov = 60;
    step_angle = player->pov/projection_plan_default_wide;

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
            SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
            SDL_RenderDrawLine(renderer, player->pos_x, player->pos_y, mouse_pos_x, mouse_pos_y);

            //draw throwed rays
            tmp_angle = player->pov;


            
            

            /*
            //draw left rays
            while (tmp_angle <= player->fov/2)
            {
               
               tmp_angle += step_angle;
            }
            tmp_angle = player->pov;

            //draw right rays
            while (tmp_angle >= player->fov/2)
            {
               
            }*/
            

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

            // variables controle

            //-----------------------------------------

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

void get_first_horiz_line_inter(float f_x, float f_y, float p_x, float p_y)
{

}

void get_collide_wall(float p_x, float p_y, float x, float y)
{
    float f_x, f_y;

    get_first_horiz_line_inter(f_x, f_y, p_x, p_y);
}

void set_player_grid_pos(player *p)
{
    float ratio_x = p->pos_x/64;
    float ratio_y = p->pos_y/64;

    p->pos_x_grid = floorf(ratio_x);
    p->pos_y_grid = floorf(ratio_y);
}

void calculate_player_orientaion_ray(float p_x, float p_y, float m_x, float m_y, float a, float b)
{
    a = (p_y - m_y)/(p_x - m_x);
    b = p_y - a*p_x;
}

void get_ray_director_vector(player *p, float mx, float my, float *s_x, float *s_y)
{
    *s_x = mx - p->pos_x;
    *s_y = my - p->pos_y;
    
}