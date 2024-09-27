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
    void setRed(unsigned char red);
    void setGreen(unsigned char green);
    void setBlue(unsigned char blue);

    // Operator overloads
    Color& operator=(const Color& other);

private:
    // Properties
    unsigned char _red;
    unsigned char _green;
    unsigned char _blue;
};

#endif //COLOR_HPP
