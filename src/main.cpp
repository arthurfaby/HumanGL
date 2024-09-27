#include "main.hpp"
#include "Point3.hpp"
#include "Renderer.hpp"

auto perspectiveProjection(const int zoom, const Point3& point3)
{
    float z = point3.getZ();
    if (z == 0)
    {
        z = 1;
    }
    return Point2(
        point3.getX() * zoom / z + 1920 / 2,
        point3.getY() * zoom / z + 1080 / 2
    );
}

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
    pWindow = SDL_CreateWindow("HumanGL",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               1920,
                               1080,
                               SDL_WINDOW_SHOWN);

    if (pWindow)
    {
        SDL_Renderer* sdlRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
        const auto renderer = Renderer(sdlRenderer);
        int zoom = 100;

        // Cube points
        auto a = Point3(-50, -50, 100);
        auto b = Point3(50, -50, 100);
        auto c = Point3(50, -50, 200);
        auto d = Point3(-50, -50, 200);
        auto e = Point3(-50, 50, 100);
        auto f = Point3(50, 50, 100);
        auto g = Point3(50, 50, 200);
        auto h = Point3(-50, 50, 200);
        auto topColor = Color(255, 0, 0);
        auto baseColor = Color(0, 0, 255);
        auto verticalColor = Color(0, 255, 0);

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

            renderer.drawLine(perspectiveProjection(zoom, a), perspectiveProjection(zoom, b), topColor);
            renderer.drawLine(perspectiveProjection(zoom, b), perspectiveProjection(zoom, c), topColor);
            renderer.drawLine(perspectiveProjection(zoom, c), perspectiveProjection(zoom, d), topColor);
            renderer.drawLine(perspectiveProjection(zoom, d), perspectiveProjection(zoom, a), topColor);

            renderer.drawLine(perspectiveProjection(zoom, e), perspectiveProjection(zoom, f), baseColor);
            renderer.drawLine(perspectiveProjection(zoom, f), perspectiveProjection(zoom, g), baseColor);
            renderer.drawLine(perspectiveProjection(zoom, g), perspectiveProjection(zoom, h), baseColor);
            renderer.drawLine(perspectiveProjection(zoom, h), perspectiveProjection(zoom, e), baseColor);

            renderer.drawLine(perspectiveProjection(zoom, a), perspectiveProjection(zoom, e), verticalColor);
            renderer.drawLine(perspectiveProjection(zoom, b), perspectiveProjection(zoom, f), verticalColor);
            renderer.drawLine(perspectiveProjection(zoom, c), perspectiveProjection(zoom, g), verticalColor);
            renderer.drawLine(perspectiveProjection(zoom, d), perspectiveProjection(zoom, h), verticalColor);

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
