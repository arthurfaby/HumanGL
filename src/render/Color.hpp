#ifndef COLOR_HPP
#define COLOR_HPP


class Color
{
public:
    // Constructors
    Color();
    Color(int red, int green, int blue);
    Color(const Color& other);

    // Destructor
    ~Color();

    // Getters
    [[nodiscard]] int getRed() const;
    [[nodiscard]] int getGreen() const;
    [[nodiscard]] int getBlue() const;

    // Setters
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);

    // Operator overloads
    Color& operator=(const Color& other);

private:
    int _red = 0;
    int _green = 0;
    int _blue = 0;

    // Methods
    void _validateColor(int& color);
};


#endif //COLOR_HPP
