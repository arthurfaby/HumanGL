#include "Renderer.hpp"

// Constructors
Renderer::Renderer(SDL_Renderer* renderer): _renderer(renderer)
{
}

// Destructor
Renderer::~Renderer()
{
    SDL_DestroyRenderer(_renderer);
}

// Getters
[[nodiscard]] SDL_Renderer* Renderer::getRenderer() const
{
    return _renderer;
}

// Setters
void Renderer::setRenderer(SDL_Renderer* renderer)
{
    _renderer = renderer;
}

// Operator overloads

// Methods
void Renderer::clear() const
{
    _setDrawColor(Color(0, 0, 0));
    SDL_RenderClear(_renderer);
}

void Renderer::clear(const Color& color) const
{
    _setDrawColor(color);
    SDL_RenderClear(_renderer);
}

void Renderer::present() const
{
    SDL_RenderPresent(_renderer);
}

// 2D rendering
void Renderer::drawPoint(const Point2& point, const Color& color) const
{
    _setDrawColor(color);
    SDL_RenderDrawPoint(_renderer,
                        point.getX(),
                        point.getY()
    );
}

void Renderer::drawLine(const Point2& start, const Point2& end, const Color& color) const
{
    _setDrawColor(color);
    SDL_RenderDrawLine(_renderer,
                       start.getX(),
                       start.getY(),
                       end.getX(),
                       end.getY());
}

void Renderer::drawEmptyRect(const Point2& topLeft, const Point2& bottomRight,
                             const Color& color) const
{
    SDL_Rect rect;

    rect.x = topLeft.getX();
    rect.y = topLeft.getY();
    rect.w = bottomRight.getX() - topLeft.getX();
    rect.h = bottomRight.getY() - topLeft.getY();
    _setDrawColor(color);
    SDL_RenderDrawRect(_renderer, &rect);
}

void Renderer::drawFillRect(const Point2& topLeft,
                            const Point2& bottomRight,
                            const Color& color) const
{
    SDL_Rect rect;

    rect.x = topLeft.getX();
    rect.y = topLeft.getY();
    rect.w = bottomRight.getX() - topLeft.getX();
    rect.h = bottomRight.getY() - topLeft.getY();
    _setDrawColor(color);
    SDL_RenderFillRect(_renderer, &rect);
}


// Private methods
void Renderer::_setDrawColor(const Color& color) const
{
    SDL_SetRenderDrawColor(_renderer,
                           color.getRed(),
                           color.getGreen(),
                           color.getBlue(),
                           SDL_ALPHA_OPAQUE);
}
