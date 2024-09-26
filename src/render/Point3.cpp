#include "Point3.hpp"

// Constructors
Point3::Point3() = default;

Point3::Point3(const float x, const float y, const float z): _x(x), _y(y), _z(z) {}

Point3::Point3(const Point3 &other) = default;

// Destructor
Point3::~Point3() = default;

// Getters
[[nodiscard]] float Point3::getX() const {
    return _x;
}

[[nodiscard]] float Point3::getY() const {
    return _y;
}

[[nodiscard]] float Point3::getZ() const {
    return _z;
}

// Setters
void Point3::setX(const float x) {
    _x = x;
}

void Point3::setY(const float y) {
    _y = y;
}

void Point3::setZ(const float z) {
    _z = z;
}

// Operator overloads
Point3 Point3::operator+(const Point3 &other) const {
    return Point3(_x + other._x, _y + other._y, _z + other._z);
}

Point3 Point3::operator-(const Point3 &other) const {
    return Point3(_x - other._x, _y - other._y, _z - other._z);
}

Point3 Point3::operator*(const Point3 &other) const {
    return Point3(_x * other._x, _y * other._y, _z * other._z);
}

Point3 Point3::operator/(const Point3 &other) const {
    return Point3(_x / other._x, _y / other._y, _z / other._z);
}

Point3& Point3::operator=(const Point3 &other) = default;