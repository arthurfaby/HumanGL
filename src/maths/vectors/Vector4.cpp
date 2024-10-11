#include "Vector4.hpp"
#include <cmath>
#include <iostream>
#include <Logger.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Default constructor.
 */
Vector4::Vector4(): Vector4(0.0f, 0.0f, 0.0f, 1.0f)
{
}

/**
 * Constructor.
 *
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
 * Copy constructor.
 *
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
 * Destructor.
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
 * Set the x component of the vector.
 *
 * @param x The new x component
 *
 * @return itself
 */
Vector4& Vector4::setX(const float x)
{
    _data[0] = x;
    return *this;
}

/**
 * Set the y component of the vector.
 *
 * @param y The new y component
 *
 * @return itself
 */
Vector4& Vector4::setY(const float y)
{
    _data[1] = y;
    return *this;
}

/**
 * Set the z component of the vector.
 *
 * @param z The new z component
 *
 * @return itself
 */
Vector4& Vector4::setZ(const float z)
{
    _data[2] = z;
    return *this;
}

/**
 * Set the w component of the vector.
 *
 * @param w The new w component
 *
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
 * Assignation operator overload.<br>
 * Assign the values of the other vector to this vector.
 *
 * @param other The vector to assign
 *
 * @return itself
 */
Vector4& Vector4::operator=(const Vector4& other)
{
    if (this != &other)
    {
        _data[0] = other._data[0];
        _data[1] = other._data[1];
        _data[2] = other._data[2];
        _data[3] = other._data[3];
    }
    return *this;
}

/**
 * Addition operator overload.<br>
 * Create a new Vector4 initialized with the sum of the left and right vectors.
 *
 * @param other The vector to add
 *
 * @return A copy of the created Vector4
 */
Vector4 Vector4::operator+(const Vector4& other) const
{
    return Vector4(
        _data[0] + other._data[0],
        _data[1] + other._data[1],
        _data[2] + other._data[2],
        _data[3] + other._data[3]
    );
}

/**
 * Addition assignment operator overload.<br>
 * Add the values of the other vector to this vector.
 *
 * @param other The vector to add
 *
 * @return itself
 */
Vector4& Vector4::operator+=(const Vector4& other)
{
    *this = *this + other;
    return *this;
}

/**
 * Subtraction operator overload.<br>
 * Create a new Vector4 initialized with the difference between the left and right vectors.
 *
 * @param other The vector to subtract
 *
 * @return A copy of the created Vector4
 */
Vector4 Vector4::operator-(const Vector4& other) const
{
    return Vector4(
        _data[0] - other._data[0],
        _data[1] - other._data[1],
        _data[2] - other._data[2],
        _data[3] - other._data[3]
    );
}

/**
 * Subtraction assignment operator overload.<br>
 * Subtract the values of the other vector to this vector.
 *
 * @param other The vector to subtract
 *
 * @return itself
 */
Vector4& Vector4::operator-=(const Vector4& other)
{
    _data[0] -= other._data[0];
    _data[1] -= other._data[1];
    _data[2] -= other._data[2];
    _data[3] -= other._data[3];
    return *this;
}

/**
 * Multiplication operator overload.<br>
 * Create a new Vector4 initialized with the product of the left and right vectors.
 *
 * @param other The vector to multiply
 *
 * @return A copy of the created Vector4
 */
Vector4 Vector4::operator*(const Vector4& other) const
{
    return Vector4(
        _data[0] * other._data[0],
        _data[1] * other._data[1],
        _data[2] * other._data[2],
        _data[3] * other._data[3]
    );
}

/**
 * Multiplication assignment operator overload.<br>
 * Multiply the values of the other vector to this vector.
 *
 * @param other The vector to multiply
 *
 * @return itself
 */
Vector4& Vector4::operator*=(const Vector4& other)
{
    _data[0] *= other._data[0];
    _data[1] *= other._data[1];
    _data[2] *= other._data[2];
    _data[3] *= other._data[3];
    return *this;
}

/**
 * Division operator overload.<br>
 * Create a new Vector4 initialized with the quotient of the left vector divided by the right vector.
 * If one of the values of the right vector is 0, return a copy of the left vector.
 *
 * @param other The vector to multiply
 *
 * @return A copy of the created Vector4 on success. Otherwise, the non-modified left vector
 */
Vector4 Vector4::operator/(const Vector4& other) const
{
    for (const float componentValue: other._data)
    {
        if (componentValue == 0.0f)
        {
            Logger::warning("Vector4::operator/(Vector4): Division by zero on a component. Operation aborted.");
            return Vector4(*this);
        }
    }
    return Vector4(
        _data[0] / other._data[0],
        _data[1] / other._data[1],
        _data[2] / other._data[2],
        _data[3] / other._data[3]
    );
}

/**
 * Division assignment operator overload.<br>
 * Divide the values of the other vector to this vector.
 *
 * @param other The vector to divide
 *
 * @return itself
 */
Vector4& Vector4::operator/=(const Vector4& other)
{
    *this = *this / other;
    return *this;
}

/**
 * Addition operator overload.<br>
 * Create a new Vector4 initialized with the sum of the left vector and the right value.
 *
 * @param other The value to add
 *
 * @return A copy of the created Vector4
 */
Vector4 Vector4::operator+(const float other) const
{
    return Vector4(
        _data[0] + other,
        _data[1] + other,
        _data[2] + other,
        _data[3] + other
    );
}

/**
 * Addition assignment operator overload.<>
 * Add the value to all components of the vector.
 *
 * @param other The value to add
 *
 * @return itself
 */
Vector4& Vector4::operator+=(const float other)
{
    *this = *this + other;
    return *this;
}

/**
 * Subtraction assignment operator overload.<br>
 * Subtract all components of the vector by the value.
 *
 * @param other The value to subtract
 *
 * @return itself
 */
Vector4 Vector4::operator-(const float other) const
{
    return Vector4(
        _data[0] - other,
        _data[1] - other,
        _data[2] - other,
        _data[3] - other
    );
}

/**
 * Subtraction assignment operator overload.<br>
 * Subtract all components of the vector by the value.
 *
 * @param other The value to subtract
 *
 * @return itself
 */
Vector4& Vector4::operator-=(const float other)
{
    *this = *this - other;
    return *this;
}

/**
 * Multiplication operator overload.<br>
 * Multiply all components of the vector by the value.
 *
 * @param other The value to multiply
 *
 * @return itself
 */
Vector4 Vector4::operator*(const float other) const
{
    return Vector4(
        _data[0] * other,
        _data[1] * other,
        _data[2] * other,
        _data[3] * other
    );
}

/**
 * Multiplication assignment operator overload.<br>
 * Multiply all components of the vector by the value.
 *
 * @param other The value to multiply
 *
 * @return itself
 */
Vector4& Vector4::operator*=(const float other)
{
    *this = *this * other;
    return *this;
}

/**
 * Division operator overload.<br>
 * Divide the all components of the vector by the value. If the value is 0, return the non-modified vector.
 *
 * @param other The value to divide by
 *
 * @return itself
 */
Vector4 Vector4::operator/(const float other) const
{
    if (other == 0)
    {
        Logger::warning("Vector4::operator/(float): Division by zero. Operation aborted.");
        return Vector4(*this);
    }
    return Vector4(
        _data[0] / other,
        _data[1] / other,
        _data[2] / other,
        _data[3] / other
    );
}

/**
 * Division assignment operator overload.<br>
 * Divide the value to all the components of the vector.
 *
 * @param other The value to divide
 *
 * @return itself
 */
Vector4& Vector4::operator/=(const float other)
{
    *this = *this / other;
    return *this;
}

/**
 * Equality operator overload.<br>
 * Check if the other vector is equal to this vector.
 *
 * @param other The vector to compare
 *
 * @return true if the vectors are equal, false otherwise
 */
bool Vector4::operator==(const Vector4& other) const
{
    return _data[0] == other._data[0] && _data[1] == other._data[1] && _data[2] == other._data[2] && _data[3] == other.
           _data[3];
}

/**
 * Inequality operator overload.<br>
 * Check if the other vector is not equal to this vector.
 *
 * @param other The vector to compare
 *
 * @return true if the vectors are not equal, false otherwise
 */
bool Vector4::operator!=(const Vector4& other) const
{
    return !(*this == other);
}

/**
 * Access operator[] overload.<br>
 * Retrieve the component at the specified index.
 *
 * @param index The index of the component
 *
 * @return The created Vector4
 */
[[nodiscard]] const float& Vector4::operator[](const int index) const {
    return _data[index];
}

/**
 * Output stream operator overload.<br>
 * Print the vector to the output stream.
 *
 * @param os The output stream
 * @param vector The vector to print
 *
 * @return The output stream
 */
std::ostream& operator<<(std::ostream& os, const Vector4& vector)
{
    const auto vectorData = vector.getData();
    os << "Vector4(" << vectorData[0] << ", " << vectorData[1] << ", " << vectorData[2] << ", " << vectorData[3] << ")";
    return os;
}

/**
 * @return A string containing the data of the vector
 */
[[nodiscard]] std::string Vector4::toString() const
{
    return "Vector4(" +
           std::to_string(_data[0]) + ", " +
           std::to_string(_data[1]) + ", " +
           std::to_string(_data[2]) + ", " +
           std::to_string(_data[3]) + ")";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Calculate the magnitude of the vector (the length of the vector).
 *
 * @return The magnitude of the vector
 */
[[nodiscard]] float Vector4::magnitude() const
{
    return sqrtf(powf(_data[0], 2) + powf(_data[1], 2) + powf(_data[2], 2) + powf(_data[3], 2));
}

/**
 * Normalize the vector (make the vector have a magnitude of 1).
 *
 * @return itself
 */
Vector4& Vector4::normalize()
{
    const float vectorMagnitude = magnitude();
    *this = *this / vectorMagnitude;
    return *this;
}

/**
 * Check if the vector is normalized (has a magnitude of 1) with a precision of 1.e-6.
 *
 * @return true if the vector is normalized, false otherwise
 */
[[nodiscard]] bool Vector4::isNormalized() const
{
    return fabsf(magnitude() - 1.0f) < 1.e-6f;
}