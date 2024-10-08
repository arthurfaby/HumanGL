#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
public:
    // Constructors
    Color() = delete;
    Color(unsigned char red, unsigned char green, unsigned char blue);
    Color(const Color& other);

    // Destructor
    ~Color();

    // Getters
    [[nodiscard]] unsigned char getRed() const;
    [[nodiscard]] unsigned char getGreen() const;
    [[nodiscard]] unsigned char getBlue() const;

    // Setters
    Color& setRed(unsigned char red);
    Color& setGreen(unsigned char green);
    Color& setBlue(unsigned char blue);

    // Operator overloads
    Color& operator=(const Color& other);

private:
    /**
     * The red component of the color. (0-255)
     */
    unsigned char _red;

    /**
     * The green component of the color. (0-255)
     */
    unsigned char _green;

    /**
     * The blue component of the color. (0-255)
     */
    unsigned char _blue;
};

#endif //COLOR_HPP
