#include "Color.hpp"

// Constructors
Color::Color() = default;

Color::Color(const int red, const int green, const int blue):
    _red(red),
    _green(green),
    _blue(blue)
{
}

Color::Color(const Color& other) = default;

// Destructor
Color::~Color() = default;

// Getters
[[nodiscard]] int Color::getRed() const
{
    return _red;
}

[[nodiscard]] int Color::getGreen() const
{
    return _green;
}

[[nodiscard]] int Color::getBlue() const
{
    return _blue;
}

// Setters
void Color::setRed(const int red)
{
    _red = red;
    _validateColor(_red);
}

void Color::setGreen(const int green)
{
    _green = green;
    _validateColor(_green);
}

void Color::setBlue(const int blue)
{
    _blue = blue;
    _validateColor(_blue);
}

// Operator overloads
Color& Color::operator=(const Color& other) = default;

// Private methods
void Color::_validateColor(int& color)
{
    if (color > 255)
    {
        color = 255;
    }
    else if (color < 0)
    {
        color = 0;
    }
}
