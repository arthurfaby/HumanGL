#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <array>
#include <Vector4.hpp>

class Matrix4
{
public:
    // Constructors
    Matrix4() = delete;
    explicit Matrix4(const std::array<float, 16>& list);
    Matrix4(const Matrix4& other) = default;

    // Destructor
    ~Matrix4() = default;

    // Getters
    [[nodiscard]] const float* getData() const;
    [[nodiscard]] Vector4 getRow(unsigned int index) const;
    [[nodiscard]] Vector4 getColumn(unsigned int index) const;

    // Operator overloads
    Matrix4& operator=(const Matrix4& other);
    Matrix4 operator*(const Matrix4& other) const;

    Vector4 operator*(const Vector4& other) const;

    // Methods
    static Matrix4 createRotationMatrix(double angleX, double angleY, double angleZ);
    static Matrix4 createRotationXMatrix(double angle);
    static Matrix4 createRotationYMatrix(double angle);
    static Matrix4 createRotationZMatrix(double angle);
    static Matrix4 createScalingMatrix(float sx, float sy, float sz);
    static Matrix4 createTranslationMatrix(float tx, float ty, float tz);
    static Matrix4 identity();
    [[nodiscard]] std::string toString() const;

private:
    /**
    * The data of the matrix such as :<br>
    *  [0, 1, 2, 3]<br>
    *  [4, 5, 6, 7]<br>
    *  [8, 9, 10, 11]<br>
    *  [12, 13, 14, 15]<br>
    */
    float _data[16]{};
};

std::ostream& operator<<(std::ostream& os, const Matrix4& matrix);

#endif //MATRIX4_HPP