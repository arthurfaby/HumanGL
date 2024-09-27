#include "Point2.hpp"

// Constructors
Point2::Point2(const float x, const float y): _x(x), _y(y)
{
}

Point2::Point2(const Point2& other) = default;

// Destructor
Point2::~Point2() = default;

// Getters
[[nodiscard]] int Point2::getX() const
{
    return static_cast<int>(_x);
}

[[nodiscard]] int Point2::getY() const
{
    return static_cast<int>(_y);
}

[[nodiscard]] float Point2::getRawX() const
{
    return _x;
}

[[nodiscard]] float Point2::getRawY() const
{
    return _y;
}

// Setters
Point2& Point2::setX(const float x)
{
    _x = x;
    return *this;
}

Point2& Point2::setY(const float y)
{
    _y = y;
    return *this;
}

// Operator overloads
auto Point2::operator+(const Point2& other) const
{
    return Point2(_x + other._x, _y + other._y);
}

auto Point2::operator-(const Point2& other) const
{
    return Point2(_x - other._x, _y - other._y);
}

Point2& Point2::operator=(const Point2& other) = default;


