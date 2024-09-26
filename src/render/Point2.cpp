#include "Point2.hpp"

// Constructors
Point2::Point2() = default;

Point2::Point2(const float x, const float y): _x(x), _y(y)
{
}

Point2::Point2(const Point2& other) = default;

// Destructor
Point2::~Point2() = default;

// Getters
[[nodiscard]] float Point2::getX() const
{
    return _x;
}

[[nodiscard]] float Point2::getY() const
{
    return _y;
}

// Setters
void Point2::setX(const float x)
{
    _x = x;
}

void Point2::setY(const float y)
{
    _y = y;
}

// Operator overloads
Point2 Point2::operator+(const Point2& other) const
{
    return Point2(_x + other._x, _y + other._y);
}

Point2 Point2::operator-(const Point2& other) const
{
    return Point2(_x - other._x, _y - other._y);
}

Point2 Point2::operator*(const Point2& other) const
{
    return Point2(_x * other._x, _y * other._y);
}

Point2 Point2::operator/(const Point2& other) const
{
    return Point2(_x / other._x, _y / other._y);
}

Point2& Point2::operator=(const Point2& other) = default;


