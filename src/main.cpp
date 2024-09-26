#include "main.hpp"


#include "render/Renderer.hpp"

int main()
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }
    /* Création de la fenêtre */
    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("HumanGL",SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               1920,
                               1080,
                               SDL_WINDOW_SHOWN);

    if (pWindow)
    {
        SDL_Renderer* sdlRenderer = SDL_CreateRenderer(
            pWindow, -1, SDL_RENDERER_ACCELERATED);
        const auto renderer = Renderer(sdlRenderer);
        auto color = Color(0, 0, 0);
        auto point1 = Point2(0, 0);
        auto point2 = Point2(100, 100);
        while (true)
        {
            SDL_Event e;
            if (SDL_PollEvent(&e))
            {
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        break;
                    }
                    if (e.key.keysym.sym == SDLK_UP)
                    {
                        point1.setX(rand() % 1920);
                        point1.setY(rand() % 1080);
                        point2.setX(rand() % 1920);
                        point2.setY(rand() % 1080);
                    }
                }
                if (e.type == SDL_QUIT)
                {
                    break;
                }
            }
            renderer.clear(Color(255, 255, 255));;
            renderer.drawLine(point1, point2, color);
            renderer.drawEmptyRect(point1, point2, color);
            renderer.present();
        }
    }
    else
    {
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }

    SDL_Quit();

    return 0;
}
