#ifndef MATRIX4_HPP
#define MATRIX4_HPP
#include <array>
#include <Vector4.hpp>

class Matrix4
{
public:
    // Constructors
    Matrix4() = default;
    explicit Matrix4(const std::array<float, 16>&);
    Matrix4(const Matrix4& other) = default;
    
    // Destructor
    ~Matrix4() = default;
    
    // Getters
    [[nodiscard]] const float* getData() const;
    [[nodiscard]] Vector4 getRowOne() const;
    [[nodiscard]] Vector4 getRowTwo() const;
    [[nodiscard]] Vector4 getRowThree() const;
    [[nodiscard]] Vector4 getRowFour() const;
    [[nodiscard]] Vector4 getColumnOne() const;
    [[nodiscard]] Vector4 getColumnTwo() const;
    [[nodiscard]] Vector4 getColumnThree() const;
    [[nodiscard]] Vector4 getColumnFour() const;

    // Operator overloads
    Matrix4& operator=(const Matrix4& other);
    Matrix4 operator*(const Matrix4& other) const;

    Vector4 operator*(const Vector4& other) const;

    [[nodiscard]] std::string toString() const;

    // Methods
    static Matrix4 createTranslationMatrix(float, float, float);
    static Matrix4 createRotationXMatrix(double);
    static Matrix4 createRotationYMatrix(double);
    static Matrix4 createRotationZMatrix(double);
    static Matrix4 createScalingMatrix(float, float, float);

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

std::ostream& operator<<(std::ostream& os, const Matrix4&);

#endif //MATRIX4_HPP
