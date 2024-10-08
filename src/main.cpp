#include "main.hpp"
#include <algorithm>
#include <vector>
#include "Logger.hpp"
#include "Point3.hpp"
#include "Renderer.hpp"

Point2 perspectiveProjection(const int zoom, const Point3& point3)
{
    float z = point3.getZ();
    if (z == 0)
    {
        z = 1;
    }
    return Point2(
        point3.getX() * zoom / z + 1000 / 2,
        point3.getY() * zoom / z + 600 / 2
    );
}

int main()
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Logger::error("Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }
    /* Création de la fenêtre */
    SDL_Window* pWindow = nullptr;
    pWindow = SDL_CreateWindow("HumanGL",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               1000,
                               600,
                               SDL_WINDOW_SHOWN);

    if (pWindow)
    {
        SDL_Renderer* sdlRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
        const auto renderer = Renderer(sdlRenderer);
        int zoom = 100;

        auto topColor = Color(255, 0, 0);
        auto baseColor = Color(0, 0, 255);
        auto verticalColor = Color(0, 255, 0);

        // Handle alpha
        SDL_SetRenderDrawBlendMode(renderer.getRenderer(), SDL_BLENDMODE_BLEND);

        while (true)
        {
            SDL_Event event;
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    break;
                }
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT)
                    {
                        a.setX(a.getX() + 1);
                    }
                    if (event.key.keysym.sym == SDLK_LEFT)
                    {
                        a.setX(a.getX() - 1);
                    }

                    if (event.key.keysym.sym == SDLK_UP)
                    {
                        a.setY(a.getY() - 1);
                    }
                    if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        a.setY(a.getY() + 1);
                    }
                    if (event.key.keysym.sym == SDLK_PAGEUP)
                    {
                        a.setZ(a.getZ() + 1);
                    }
                    if (event.key.keysym.sym == SDLK_PAGEDOWN)
                    {
                        a.setZ(a.getZ() - 1);
                    }
                    if (event.key.keysym.sym == SDLK_r)
                    {
                        a = Point3(-50, -50, 100);
                    }
                    if (event.key.keysym.sym == SDLK_KP_PLUS)
                    {
                        zoom += 1;
                    }
                    if (event.key.keysym.sym == SDLK_KP_MINUS)
                    {
                        zoom -= 1;
                    }
                }
            }

            renderer.clear(Color(255, 255, 255));

            std::vector<Point2> polygon = {
                {200, 200},
                {300, 150},
                {250, 400},
                {100, 200},
                {100, 100}
            };
            renderer.drawPolygon(polygon, topColor);
            renderer.drawLine({200, 200}, {300, 150}, verticalColor);
            renderer.drawLine({300, 150}, {250, 400}, verticalColor);
            renderer.drawLine({250, 400}, {100, 200}, verticalColor);
            renderer.drawLine({100, 200}, {100, 100}, verticalColor);
            renderer.drawLine({100, 100}, {200, 200}, verticalColor);

            renderer.present();
        }
    }
    else
    {
        Logger::error("Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }

    SDL_Quit();

    return 0;
}