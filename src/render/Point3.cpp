#include "Point3.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Constructor
 * @param x The x component of the point
 * @param y The y component of the point
 * @param z The z component of the point
 */
Point3::Point3(const float x, const float y, const float z): _x(x), _y(y), _z(z)
{
}

/**
 * Copy constructor
 * @param other The other point to copy
 */
Point3::Point3(const Point3& other) = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Descructor
 */
Point3::~Point3() = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The x component of the point
 */
[[nodiscard]] float Point3::getX() const
{
 return _x;
}

/**
 * @return The y component of the point
 */
[[nodiscard]] float Point3::getY() const
{
 return _y;
}

/**
 * @return The z component of the point
 */
[[nodiscard]] float Point3::getZ() const
{
 return _z;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Set the x component of the point
 * @param x The new x component of the point
 * @return itself
 */
Point3& Point3::setX(const float x)
{
 _x = x;
 return *this;
}

/**
 * Set the y component of the point
 * @param y The new y component of the point
 * @return itself
 */
Point3& Point3::setY(const float y)
{
 _y = y;
 return *this;
}

/**
 * Set the z component of the point
 * @param z The new z component of the point
 * @return itself
 */
Point3& Point3::setZ(const float z)
{
 _z = z;
 return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator overloads
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Addition operator overload
 * @param other The other point to add
 * @return A new point which is the sum of the two points
 */
auto Point3::operator+(const Point3& other) const
{
 return Point3(_x + other._x, _y + other._y, _z + other._z);
}

/**
 * Subtraction operator overload
 * @param other The other point to subtract
 * @return A new point which is the difference of the two points
 */
auto Point3::operator-(const Point3& other) const
{
 return Point3(_x - other._x, _y - other._y, _z - other._z);
}

/**
 * Assignation operator overload
 * @param other The other point to assign
 * @return itself
 */
Point3& Point3::operator=(const Point3& other) = default;
