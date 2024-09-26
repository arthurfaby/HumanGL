#include "main.hpp"

int main()
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    /* Création de la fenêtre */
    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                              SDL_WINDOWPOS_UNDEFINED,
                                                              1920,
                                                              1080,
                                                              SDL_WINDOW_SHOWN);

    if( pWindow )
    {
        SDL_Renderer* renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
        while(true)
        {
            SDL_Event e;
            if (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    break;
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawLine(renderer, 500, 500, 700, 700);
            SDL_RenderPresent(renderer);

            SDL_Delay(16);
        }
    }
    else
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }

    SDL_Quit();

    return 0;
}
