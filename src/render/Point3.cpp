#include "Point3.hpp"

// Constructors
Point3::Point3(const float x, const float y, const float z): _x(x), _y(y), _z(z)
{
}

Point3::Point3(const Point3& other) = default;

// Destructor
Point3::~Point3() = default;

// Getters
[[nodiscard]] float Point3::getX() const
{
    return _x;
}

[[nodiscard]] float Point3::getY() const
{
    return _y;
}

[[nodiscard]] float Point3::getZ() const
{
    return _z;
}

// Setters
Point3& Point3::setX(const float x)
{
    _x = x;
    return *this;
}

Point3& Point3::setY(const float y)
{
    _y = y;
    return *this;
}

Point3& Point3::setZ(const float z)
{
    _z = z;
    return *this;
}

// Operator overloads
auto Point3::operator+(const Point3& other) const
{
    return Point3(_x + other._x, _y + other._y, _z + other._z);
}

auto Point3::operator-(const Point3& other) const
{
    return Point3(_x - other._x, _y - other._y, _z - other._z);
}

Point3& Point3::operator=(const Point3& other) = default;
