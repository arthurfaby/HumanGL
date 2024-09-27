#include "Color.hpp"

// Constructors
Color::Color(const unsigned char red, const unsigned char green, const unsigned char blue):
    _red(red),
    _green(green),
    _blue(blue)
{
}

Color::Color(const Color& other) = default;

// Destructor
Color::~Color() = default;

// Getters
[[nodiscard]] unsigned char Color::getRed() const
{
    return _red;
}

[[nodiscard]] unsigned char Color::getGreen() const
{
    return _green;
}

[[nodiscard]] unsigned char Color::getBlue() const
{
    return _blue;
}

// Setters
void Color::setRed(const unsigned char red)
{
    _red = red;
}

void Color::setGreen(const unsigned char green)
{
    _green = green;
}

void Color::setBlue(const unsigned char blue)
{
    _blue = blue;
}

// Operator overloads
Color& Color::operator=(const Color& other) = default;
