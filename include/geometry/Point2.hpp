#ifndef POINT2_HPP
#define POINT2_HPP

class Point2
{
public:
    // Constructors
    Point2() = delete;
    Point2(float x, float y);
    Point2(const Point2& other);

    // Destructor
    ~Point2();

    // Getters
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] float getRawX() const;
    [[nodiscard]] float getRawY() const;

    // Setters
    Point2& setX(float x);
    Point2& setY(float y);

    // Operator overloads
    auto operator+(const Point2& other) const;
    auto operator-(const Point2& other) const;
    Point2& operator=(const Point2& other);

private:
    /**
     * The x component of the point.
     */
    float _x;

    /**
     * The y component of the point.
     */
    float _y;
};

#endif //POINT2_HPP
