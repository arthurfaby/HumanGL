#ifndef VECTOR4_HPP
#define VECTOR4_HPP
#include <ostream>

class Vector4
{
public:
    // Constructors
    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector4& other);

    // Destructor
    ~Vector4();

    // Getters
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getZ() const;
    [[nodiscard]] float getW() const;
    [[nodiscard]] const float* getData() const;

    // Setters
    Vector4& setX(float x);
    Vector4& setY(float y);
    Vector4& setZ(float z);
    Vector4& setW(float w);

    // Operator overloads
    Vector4& operator=(const Vector4& other);
    Vector4& operator+(const Vector4& other);
    Vector4& operator+=(const Vector4& other);
    Vector4& operator-(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    Vector4& operator*(const Vector4& other);
    Vector4& operator*=(const Vector4& other);
    Vector4& operator/(const Vector4& other);
    Vector4& operator/=(const Vector4& other);

    Vector4& operator+(float other);
    Vector4& operator+=(float other);
    Vector4& operator-(float other);
    Vector4& operator-=(float other);
    Vector4& operator*(float other);
    Vector4& operator*=(float other);
    Vector4& operator/(float other);
    Vector4& operator/=(float other);

    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;

    std::ostream& operator<<(std::ostream& os) const;
    [[nodiscard]] std::string toString() const;

    // Methods
    [[nodiscard]] float magnitude() const;
    Vector4& normalize();
    [[nodiscard]] bool isNormalized() const;

private:
    /**
    * The data of the vector.
    * [0] = x -- The x component of the vector.
    * [1] = y -- The y component of the vector.
    * [2] = z -- The z component of the vector.
    * [3] = w -- The w component of the vector (used for homogenous coordinates).
    */
    float _data[4]{};
};

#endif //VECTOR4_HPP
