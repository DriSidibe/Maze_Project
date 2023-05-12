#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * set - ...
 */
int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    return 0;
}

/**
 *
 */
int clearWindow(SDL_Renderer *Renderer)
{
	if(0 != SDL_RenderClear(renderer))
	{
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
		goto Quit;
	}

	return 0;
}

int run_2D(int argc, char **argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	int statut = EXIT_FAILURE;

	SDL_Color orange = {255, 127, 40, 255};

	if(0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		goto Quit;
	}
	window = SDL_CreateWindow("MAZE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN);
	if(NULL == window)
	{
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
		goto Quit;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(NULL == renderer)
	{
		fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
		goto Quit;
	}

	/* C’est à partir de maintenant que ça se passe. */
	if(0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
	{
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
		goto Quit;
	}

	setWindowColor(renderer, orange);

	statut = EXIT_SUCCESS;
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	
Quit:
	if(NULL != renderer)
		SDL_DestroyRenderer(renderer);
	if(NULL != window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return statut;
}

