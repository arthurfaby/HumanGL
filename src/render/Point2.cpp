#include "Point2.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Constructor
 * @param x The x component of the point
 * @param y The y component of the point
 */
Point2::Point2(const float x, const float y): _x(x), _y(y)
{
}

/**
 * Copy constructor
 * @param other The other point to copy
 */
Point2::Point2(const Point2& other) = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Destructor
 */
Point2::~Point2() = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The x component of the point as an integer
 */
[[nodiscard]] int Point2::getX() const
{
 return static_cast<int>(_x);
}

/**
 * @return The y component of the point as an integer
 */
[[nodiscard]] int Point2::getY() const
{
 return static_cast<int>(_y);
}

/**
 * @return The x component of the point as a float
 */
[[nodiscard]] float Point2::getRawX() const
{
 return _x;
}

/**
 * @return The y component of the point as a float
 */
[[nodiscard]] float Point2::getRawY() const
{
 return _y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Set the x component of the point
 * @param x The new x component of the point
 * @return itself
 */
Point2& Point2::setX(const float x)
{
 _x = x;
 return *this;
}

/**
 * Set the y component of the point
 * @param y The new y component of the point
 * @return itself
 */
Point2& Point2::setY(const float y)
{
 _y = y;
 return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator overloads
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Add two points together
 * @param other The other point to add
 * @return A new point which is the sum of the two points
 */
auto Point2::operator+(const Point2& other) const
{
 return Point2(_x + other._x, _y + other._y);
}

/**
 * Subtract one point from another
 * @param other The other point to subtract
 * @return A new point which is the difference of the two points
 */
auto Point2::operator-(const Point2& other) const
{
 return Point2(_x - other._x, _y - other._y);
}

/**
 * Assignation operator overload
 * @param other The other point to assign
 * @return itself
 */
Point2& Point2::operator=(const Point2& other) = default;


