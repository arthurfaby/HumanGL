#include "Vector4.hpp"
#include <cmath>
#include <iostream>
#include <Logger.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Default constructor
 */
Vector4::Vector4(): Vector4(0.0f, 0.0f, 0.0f, 1.0f)
{
}

/**
 * Constructor
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 * @param w The w component of the vector
 */
Vector4::Vector4(const float x, const float y, const float z, const float w)
{
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
    _data[3] = w;
}

/**
 * Copy constructor
 * @param other The vector to copy
 */
Vector4::Vector4(const Vector4& other)
{
    _data[0] = other._data[0];
    _data[1] = other._data[1];
    _data[2] = other._data[2];
    _data[3] = other._data[3];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Destructor
 */
Vector4::~Vector4() = default;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The x component of the vector
 */
[[nodiscard]] float Vector4::getX() const
{
    return _data[0];
}

/**
 * @return The y component of the vector
 */
[[nodiscard]] float Vector4::getY() const
{
    return _data[1];
}

/**
 * @return The z component of the vector
 */
[[nodiscard]] float Vector4::getZ() const
{
    return _data[2];
}

/**
 * @return The w component of the vector
 */
[[nodiscard]] float Vector4::getW() const
{
    return _data[3];
}

/**
 * @return The data of the vector
 */
[[nodiscard]] const float* Vector4::getData() const
{
    return _data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setters
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Set the x component of the vector
 * @param x The new x component
 * @return itself
 */
Vector4& Vector4::setX(const float x)
{
    _data[0] = x;
    return *this;
}

/**
 * Set the y component of the vector
 * @param y The new y component
 * @return itself
 */
Vector4& Vector4::setY(const float y)
{
    _data[1] = y;
    return *this;
}

/**
 * Set the z component of the vector
 * @param z The new z component
 * @return itself
 */
Vector4& Vector4::setZ(const float z)
{
    _data[2] = z;
    return *this;
}

/**
 * Set the w component of the vector
 * @param w The new w component
 * @return itself
 */
Vector4& Vector4::setW(const float w)
{
    _data[3] = w;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator overloads
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Assignation operator overload. Assign the values of the other vector to this vector
 * @param other The vector to assign
 * @return itself
 */
Vector4& Vector4::operator=(const Vector4& other)
{
    _data[0] = other._data[0];
    _data[1] = other._data[1];
    _data[2] = other._data[2];
    _data[3] = other._data[3];
    return *this;
}

/**
 * Addition operator overload. Add the values of the other vector to this vector
 * @param other The vector to add
 * @return itself
 */
Vector4& Vector4::operator+(const Vector4& other)
{
    _data[0] += other._data[0];
    _data[1] += other._data[1];
    _data[2] += other._data[2];
    _data[3] += other._data[3];
    return *this;
}

/**
 * Addition assignment operator overload. Add the values of the other vector to this vector
 * @param other The vector to add
 * @return itself
 */
Vector4& Vector4::operator+=(const Vector4& other)
{
    return *this + other;
}

/**
 * Subtraction operator overload. Subtract the values of the other vector to this vector
 * @param other The vector to subtract
 * @return itself
 */
Vector4& Vector4::operator-(const Vector4& other)
{
    _data[0] -= other._data[0];
    _data[1] -= other._data[1];
    _data[2] -= other._data[2];
    _data[3] -= other._data[3];
    return *this;
}

/**
 * Subtraction assignment operator overload. Subtract the values of the other vector to this vector
 * @param other The vector to subtract
 * @return itself
 */
Vector4& Vector4::operator-=(const Vector4& other)
{
    return *this - other;
}

/**
 * Multiplication operator overload. Multiply the values of the other vector to this vector
 * @param other The vector to multiply
 * @return itself
 */
Vector4& Vector4::operator*(const Vector4& other)
{
    _data[0] *= other._data[0];
    _data[1] *= other._data[1];
    _data[2] *= other._data[2];
    _data[3] *= other._data[3];
    return *this;
}

/**
 * Multiplication assignment operator overload. Multiply the values of the other vector to this vector
 * @param other The vector to multiply
 * @return itself
 */
Vector4& Vector4::operator*=(const Vector4& other)
{
    return *this * other;
}

/**
 * Division operator overload. Divide the values of the other vector to this vector
 * @param other The vector to divide
 * @return itself
 */
Vector4& Vector4::operator/(const Vector4& other)
{
    _data[0] /= other._data[0];
    _data[1] /= other._data[1];
    _data[2] /= other._data[2];
    _data[3] /= other._data[3];
    return *this;
}

/**
 * Division assignment operator overload. Divide the values of the other vector to this vector
 * @param other The vector to divide
 * @return itself
 */
Vector4& Vector4::operator/=(const Vector4& other)
{
    return *this / other;
}

/**
 * Addition operator overload. Add the value to all the components of the vector
 * @param other The value to add
 * @return itself
 */
Vector4& Vector4::operator+(const float other)
{
    _data[0] += other;
    _data[1] += other;
    _data[2] += other;
    _data[3] += other;
    return *this;
}

/**
 * Addition assignment operator overload. Add the value to all the components of the vector
 * @param other The value to add
 * @return itself
 */
Vector4& Vector4::operator+=(const float other)
{
    return *this + other;
}

/**
 * Subtraction operator overload. Subtract the value to all the components of the vector
 * @param other The value to subtract
 * @return itself
 */
Vector4& Vector4::operator-(const float other)
{
    _data[0] -= other;
    _data[1] -= other;
    _data[2] -= other;
    _data[3] -= other;
    return *this;
}

/**
 * Subtraction assignment operator overload. Subtract the value to all the components of the vector
 * @param other The value to subtract
 * @return itself
 */
Vector4& Vector4::operator-=(const float other)
{
    return *this - other;
}

/**
 * Multiplication operator overload. Multiply the value to all the components of the vector
 * @param other The value to multiply
 * @return itself
 */
Vector4& Vector4::operator*(const float other)
{
    _data[0] *= other;
    _data[1] *= other;
    _data[2] *= other;
    _data[3] *= other;
    return *this;
}

/**
 * Multiplication assignment operator overload. Multiply the value to all the components of the vector
 * @param other The value to multiply
 * @return itself
 */
Vector4& Vector4::operator*=(const float other)
{
    return *this * other;
}

/**
 * Division operator overload. Divide the value to all the components of the vector
 * @param other The value to divide
 * @return itself
 */
Vector4& Vector4::operator/(const float other)
{
    _data[0] /= other;
    _data[1] /= other;
    _data[2] /= other;
    _data[3] /= other;
    return *this;
}

/**
 * Division assignment operator overload. Divide the value to all the components of the vector
 * @param other The value to divide
 * @return itself
 */
Vector4& Vector4::operator/=(const float other)
{
    return *this / other;
}

/**
 * Equality operator overload. Check if the other vector is equal to this vector
 * @param other The vector to compare
 * @return true if the vectors are equal, false otherwise
 */
bool Vector4::operator==(const Vector4& other) const
{
    return _data[0] == other._data[0] && _data[1] == other._data[1] && _data[2] == other._data[2] && _data[3] == other.
           _data[3];
}

/**
 * Inequality operator overload. Check if the other vector is not equal to this vector
 * @param other The vector to compare
 * @return true if the vectors are not equal, false otherwise
 */
bool Vector4::operator!=(const Vector4& other) const
{
    return !(*this == other);
}

/**
 * Output stream operator overload. Print the vector to the output stream
 * @param os The output stream
 * @return The output stream
 */
std::ostream& Vector4::operator<<(std::ostream& os) const
{
    os << "Vector4(" << _data[0] << ", " << _data[1] << ", " << _data[2] << ", " << _data[3] << ")";
    return os;
}

[[nodiscard]] std::string Vector4::toString() const
{
    return "Vector4(" + std::to_string(_data[0]) + ", " + std::to_string(_data[1]) + ", " +
           std::to_string(_data[2]) +
           ", " + std::to_string(_data[3]) + ")";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Calculate the magnitude of the vector (the length of the vector)
 * @return The magnitude of the vector
 */
[[nodiscard]] float Vector4::magnitude() const
{
    return sqrtf(_data[0] * _data[0] + _data[1] * _data[1] + _data[2] * _data[2] + _data[3] * _data[3]);
}

/**
 * Normalize the vector (make the vector have a magnitude of 1)
 * @return itself
 */
Vector4& Vector4::normalize()
{
    const float vectorMagnitude = magnitude();
    return *this / vectorMagnitude;
}

/**
 * Check if the vector is normalized (has a magnitude of 1) with a precision of 1.e-6
 * @return true if the vector is normalized, false otherwise
 */
[[nodiscard]] bool Vector4::isNormalized() const
{
    return abs(magnitude() - 1.0f) < 1.e-6f;
}