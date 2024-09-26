#ifndef POINT2_HPP
#define POINT2_HPP


class Point2
{
public:
    // Constructors
    Point2();
    Point2(float x, float y);
    Point2(const Point2& other);

    // Destructor
    ~Point2();

    // Getters
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;

    // Setters
    void setX(float x);
    void setY(float y);

    // Operator overloads
    Point2 operator+(const Point2& other) const;
    Point2 operator-(const Point2& other) const;
    Point2 operator*(const Point2& other) const;
    Point2 operator/(const Point2& other) const;
    Point2& operator=(const Point2& other);

private:
    float _x = 0;
    float _y = 0;
};


#endif //POINT2_HPP
