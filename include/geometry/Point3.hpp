#ifndef POINT3_HPP
#define POINT3_HPP

class Point3
{
public:
    // Constructors
    Point3() = delete;
    Point3(float x, float y, float z);
    Point3(const Point3& other);

    // Destructor
    ~Point3();

    // Getters
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getZ() const;

    // Setters
    Point3& setX(float x);
    Point3& setY(float y);
    Point3& setZ(float z);

    // Operator overloads
    Point3 operator+(const Point3& other) const;
    Point3 operator-(const Point3& other) const;
    Point3& operator=(const Point3& other);

private:
    /**
     * The x component of the point.
     */
    float _x;

    /**
     * The y component of the point.
     */
    float _y;

    /**
     * The z component of the point.
     */
    float _z;
};

#endif //POINT3_HPP
