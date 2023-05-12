#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../my_includes/constants.h"
#include "../my_includes/player.h"





void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

int run_2D(int argc, char **argv[])
{

    // intialization
	SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
	SDL_Event events;
    int isOpen = 1;
    player *player = NULL;
    
    player = malloc(sizeof(player));
    player->pos_x = player_default_x_pos;
    player->pos_y = player_default_y_pos;
    player->step = player_default_step;

    //----------------------------------

	
    SDL_Color orange = {255, 127, 40, 255};
	

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
	if (SDL_CreateWindowAndRenderer(map_width + 40, map_height + 40, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

	SDL_Rect map = {
        20, 20, map_width, map_height
    };
    

    while (isOpen)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
                case SDL_QUIT:
                    isOpen = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (events.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            player->pos_x--;;
                            break;
                        case SDLK_RIGHT:
                            player->pos_x++;
                            break;
                        case SDLK_UP:
                            player->pos_y--;
                            break;
                        case SDLK_DOWN:
                            player->pos_y++;
                            break;
                    }
                    break;
            }

			/* C’est à partir de maintenant que ça se passe. */
			if(0 != SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255))
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
				SDL_Quit(); 
				return EXIT_FAILURE;
			}
			SDL_RenderClear( renderer );

			// drawwing area
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
                            i*wall_default_brick_size + 20, j*wall_default_brick_size + 20,
                            wall_default_brick_size, wall_default_brick_size
                        };
                        SDL_RenderFillRect( renderer, &r );
                    }
                }
            }

            //draw player
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            DrawCircle(renderer, player->pos_x + 20, player->pos_y + 20, 5);
			

			//-----------------------------------------

			SDL_RenderPresent(renderer);
			if(0 != SDL_RenderClear(renderer))
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
					SDL_Quit(); 
					return EXIT_FAILURE;
				}
        	}
    }
    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
	
    return 0;
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
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
