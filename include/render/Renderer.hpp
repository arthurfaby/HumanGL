#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "Color.hpp"
# include "main.hpp"
#include "Point2.hpp"

class Renderer
{
public:
    // Constructors
    Renderer() = delete;
    explicit Renderer(SDL_Renderer* renderer);

    // Destructor
    ~Renderer();

    // Getters
    [[nodiscard]] SDL_Renderer* getRenderer() const;

    // Setters
    void setRenderer(SDL_Renderer* renderer);

    // Operator overloads

    // Methods
    void clear() const;
    void clear(const Color& color) const;
    void present() const;

    // 2D rendering
    void drawPoint(const Point2& point, const Color& color) const;
    void drawLine(const Point2& start, const Point2& end, const Color& color) const;
    void drawEmptyRect(const Point2& topLeft,
                       const Point2& bottomRight,
                       const Color& color) const;
    void drawFillRect(const Point2& topLeft,
                      const Point2& bottomRight,
                      const Color& color) const;

private:
    // Properties
    SDL_Renderer* _renderer = nullptr;

    // Methods
    void _setDrawColor(const Color& color) const;
};

#endif //RENDERER_HPP
