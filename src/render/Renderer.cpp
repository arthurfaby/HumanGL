#include "Renderer.hpp"
#include "triangulatePolygon.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Constructor.
 *
 * @param renderer Instance of the SDL renderer
 */
Renderer::Renderer(SDL_Renderer* renderer): _renderer(renderer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Destructor.
 */
Renderer::~Renderer()
{
    SDL_DestroyRenderer(_renderer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The instance of the SDL renderer
 */
[[nodiscard]] SDL_Renderer* Renderer::getRenderer() const
{
    return _renderer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Set the instance of the SDL renderer.
 *
 * @param renderer Instance of the SDL renderer
 */
void Renderer::setRenderer(SDL_Renderer* renderer)
{
    _renderer = renderer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Clear the renderer with a black color.
 */
void Renderer::clear() const
{
    _setDrawColor(Color(0, 0, 0));
    SDL_RenderClear(_renderer);
}

/**
 * Clear the renderer with a specific color.
 *
 * @param color The color to clear the renderer with
 */
void Renderer::clear(const Color& color) const
{
    _setDrawColor(color);
    SDL_RenderClear(_renderer);
}

/**
 * Present the renderer.
 */
void Renderer::present() const
{
    SDL_RenderPresent(_renderer);
}

/**
 * Draw a point on the renderer.
 *
 * @param point The point to draw
 * @param color The color of the point
 */
void Renderer::drawPoint(const Point2& point, const Color& color) const
{
    _setDrawColor(color);
    SDL_RenderDrawPoint(_renderer, point.getX(), point.getY());
}

/**
 * Draw a line on the renderer.
 *
 * @param start The start point of the line
 * @param end The end point of the line
 * @param color The color of the line
 */
void Renderer::drawLine(const Point2& start, const Point2& end, const Color& color) const
{
    _setDrawColor(color);
    SDL_RenderDrawLine(_renderer, start.getX(), start.getY(), end.getX(), end.getY());
}

/**
 * Draw an empty rectangle on the renderer.
 *
 * @param topLeft The top left point of the rect
 * @param bottomRight The bottom right point of the rect
 * @param color The color of the rect
 */
void Renderer::drawEmptyRect(const Point2& topLeft, const Point2& bottomRight, const Color& color) const
{
    SDL_Rect rect;

    rect.x = topLeft.getX();
    rect.y = topLeft.getY();
    rect.w = bottomRight.getX() - topLeft.getX();
    rect.h = bottomRight.getY() - topLeft.getY();
    _setDrawColor(color);
    SDL_RenderDrawRect(_renderer, &rect);
}

/**
 * Draw a filled rectangle on the renderer.
 *
 * @param topLeft The top left point of the rect
 * @param bottomRight The bottom right point of the rect
 * @param color The color of the rect
 */
void Renderer::drawFillRect(const Point2& topLeft, const Point2& bottomRight, const Color& color) const
{
    SDL_Rect rect;

    rect.x = topLeft.getX();
    rect.y = topLeft.getY();
    rect.w = bottomRight.getX() - topLeft.getX();
    rect.h = bottomRight.getY() - topLeft.getY();
    _setDrawColor(color);
    SDL_RenderFillRect(_renderer, &rect);
}

/**
 * Draw a polygon on the renderer.
 *
 * @param points The points of the polygon
 * @param color The color of the polygon
 */
void Renderer::drawPolygon(const std::vector<Point2>& points, const Color& color) const
{
    std::vector<Point2> verticesPoints = triangulatePolygon(points);
    std::vector<SDL_Vertex> verts;

    for (const auto& verticesPoint: verticesPoints)
    {
        verts.push_back(SDL_Vertex{
            SDL_FPoint{static_cast<float>(verticesPoint.getX()), static_cast<float>(verticesPoint.getY())},
            SDL_Color{color.getRed(), color.getGreen(), color.getBlue(), 255},
            SDL_FPoint{0}
        });
    }
    SDL_RenderGeometry(_renderer, nullptr, verts.data(), static_cast<int>(verts.size()), nullptr, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Set the draw color of the renderer.
 *
 * @param color The color to set the renderer to
 */
void Renderer::_setDrawColor(const Color& color) const
{
    SDL_SetRenderDrawColor(_renderer, color.getRed(), color.getGreen(), color.getBlue(),SDL_ALPHA_OPAQUE);
}