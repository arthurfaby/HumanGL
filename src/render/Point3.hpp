#ifndef POINT3_HPP
#define POINT3_HPP

class Point3 {
public:
    // Constructors
    Point3();
    Point3(float x, float y, float z);
    Point3(const Point3 &other);

    // Destructor
    ~Point3();

    // Getters
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getZ() const;

    // Setters
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    // Operator overloads
    Point3 operator+(const Point3 &other) const;
    Point3 operator-(const Point3 &other) const;
    Point3 operator*(const Point3 &other) const;
    Point3 operator/(const Point3 &other) const;
    Point3& operator=(const Point3 &other);

private:
    float _x = 0;
    float _y = 0;
    float _z = 0;


};



#endif //POINT3_HPP
