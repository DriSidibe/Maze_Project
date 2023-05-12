#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>


int run_2D(int argc, char **argv[])
{

	SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
	SDL_Event events;
    int isOpen = 1;

	
    SDL_Color orange = {255, 127, 40, 255};
	

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
	if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

	SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;
    

    while (isOpen)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
                case SDL_QUIT:
                    isOpen = 0;
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

			SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
			SDL_RenderFillRect( renderer, &r );

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

