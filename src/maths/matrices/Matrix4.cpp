#include <array>
#include <cmath>
#include <Logger.hpp>
#include <Matrix4.hpp>
#include <sstream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Construct a new Matrix4 object using an array of 16 float values.
 *
 * @param list An array of 16 float values to initialize the matrix with
 */
Matrix4::Matrix4(const std::array<float, 16>& list)
{
    for (int i = 0; i < 16; ++i)
    {
        _data[i] = list[i];
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The data of the matrix
 */
[[nodiscard]] const float* Matrix4::getData() const
{
    return _data;
}

/**
 * Get the row of the matrix at the index.
 *
 * @param index The index of the row to get
 *
 * @throw std::out_of_range If the index is not between 0 and 3
 *
 * @return The row of the matrix at the index
 */
Vector4 Vector4::getRow(const unsigned int index) const
{
    if (index > 3)
    {
        throw std::out_of_range("The index must be between 0 and 3");
    }
    return Vector4(_data[index * 4 + 0], _data[index * 4 + 1], _data[index * 4 + 2], _data[index * 4 + 3]);
}

/**
 * Get the column of the matrix at the index.
 *
 * @param index The index of the column to get
 *
 * @throw std::out_of_range If the index is not between 0 and 3
 *
 * @return The column of the matrix at the index
 */
Vector4 Vector4::getColumn(const int index) const
{
    if (index < 0 || index > 3)
    {
        throw std::out_of_range("The index must be between 0 and 3");
    }
    return Vector4(_data[0 + index], _data[4 + index], _data[8 + index], _data[12 + index]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator overloads
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Assignation operator overload.<br>
 * Assign the values of the other matrix to this matrix.
 *
 * @param other The matrix to assign
 *
 * @return itself
 */
Matrix4& Matrix4::operator=(const Matrix4& other)
{
    if (this != &other)
    {
        const float* otherData = other.getData();

        for (int i = 0; i < 16; ++i)
        {
            _data[i] = otherData[i];
        }
    }
    return *this;
}

/**
 * Multiplication operator overload.<br>
 * Create a new Matrix4 initialized with the product of the left and right matrices.
 *
 * @param other The matrix to multiply by
 *
 * @return A copy of the created Matrix4
 */
Matrix4 Matrix4::operator*(const Matrix4& other) const
{
    const std::array rows = {getRow(0), getRow(1), getRow(2), getRow(3)};
    const std::array columns = {
        other.getColumn(0),
        other.getColumn(1),
        other.getColumn(2),
        other.getColumn(3)
    };
    std::vector<float> resVector;

    for (const Vector4& row: rows)
    {
        for (const Vector4& col: columns)
        {
            resVector.push_back(row[0] * col[0] + row[1] * col[1] + row[2] * col[2] + row[3] * col[3]);
        }
    }

    // Convert the std::vector<float> to std::array<float, 16>
    std::array<float, 16> resultArray{};
    std::copy(resVector.begin(), resVector.end(), resultArray.begin());

    return Matrix4(resultArray);
}

/**
 * Multiplication operator overload.<br>
 * Create a new Vector4 initialized with the product of the left matrix by the right vector.
 *
 * @param other The vector to multiply
 *
 * @return A copy of the created Vector4
 */
Vector4 Matrix4::operator*(const Vector4& other) const
{
    const float otherX = other.getX();
    const float otherY = other.getY();
    const float otherZ = other.getZ();
    const float otherW = other.getW();

    const float x = _data[0] * otherX + _data[1] * otherY + _data[2] * otherZ + _data[3] * otherW;
    const float y = _data[4] * otherX + _data[5] * otherY + _data[6] * otherZ + _data[7] * otherW;
    const float z = _data[8] * otherX + _data[9] * otherY + _data[10] * otherZ + _data[11] * otherW;
    const float w = _data[12] * otherX + _data[13] * otherY + _data[14] * otherZ + _data[15] * otherW;

    return Vector4(x, y, z, w);
}

/**
 * Output stream operator overload.<br>
 * Print the matrix to the output stream.
 *
 * @param os The output stream
 * @param matrix The matrix to print
 *
 * @return The output stream
 */
std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
{
    const auto matrixData = matrix.getData();
    os << "Matrix4("
            << "Row1: [" << matrixData[0] << ", " << matrixData[1] << ", " << matrixData[2] << ", " << matrixData[3] <<
            "], "
            << "Row2: [" << matrixData[4] << ", " << matrixData[5] << ", " << matrixData[6] << ", " << matrixData[7] <<
            "], "
            << "Row3: [" << matrixData[8] << ", " << matrixData[9] << ", " << matrixData[10] << ", " << matrixData[11]
            << "], "
            << "Row4: [" << matrixData[12] << ", " << matrixData[13] << ", " << matrixData[14] << ", " << matrixData[15]
            << "])";
    return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Create a rotation matrix for the X, Y and Z axis.
 *
 * @param angleX The angle in radians to apply on the x-axis
 * @param angleY The angle in radians to apply on the y-axis
 * @param angleZ The angle in radians to apply on the z-axis
 *
 * @return The created rotation matrix
 */
Matrix4 Matrix4::createRotationMatrix(const double angleX, const double angleY, const double angleZ)
{
    return createRotationXMatrix(angleX) * createRotationYMatrix(angleY) * createRotationZMatrix(angleZ);
}

/**
 * Create a rotation matrix for the X axis such as :<br>
 *  [1, 0, 0, 0]<br>
 *  [0, cos(angle), -sin(angle), 0]<br>
 *  [0, sin(angle), cos(angle), 0]<br>
 *  [0, 0, 0, 1 ]<br>
 *
 * @param angle The angle in radians of type double
 *
 * @return The created rotation matrix
 */
Matrix4 Matrix4::createRotationXMatrix(const double angle)
{
    const auto cosAngleF = static_cast<float>(cos(angle));
    const auto sinAngleF = static_cast<float>(sin(angle));

    //@formatter:off
    return Matrix4({
        1,         0,          0, 0,
        0, cosAngleF, -sinAngleF, 0,
        0, sinAngleF,  cosAngleF, 0,
        0,         0,          0, 1
    });
    //@formatter:on
}

/**
 * Create a rotation matrix for the Y axis such as :<br>
 *  [cos(angle), 0, sin(angle), 0]<br>
 *  [0, 1, 0, 0]<br>
 *  [-sin(angle), 0, cos(angle), 0]<br>
 *  [0, 0, 0, 1 ]<br>
 *
 * @param angle The angle in radians of type double
 *
 * @return The created rotation matrix
 */
Matrix4 Matrix4::createRotationYMatrix(const double angle)
{
    const auto cosAngleF = static_cast<float>(cos(angle));
    const auto sinAngleF = static_cast<float>(sin(angle));

    //@formatter:off
    return Matrix4({
         cosAngleF, 0, sinAngleF, 0,
                 0, 1,         0, 0,
        -sinAngleF, 0, cosAngleF, 0,
                 0, 0,         0, 1
    });
    //@formatter:on
}

/**
 * Create a rotation matrix for the Z axis such as :<br>
 *  [cos(angle), -sin(angle), 0, 0]<br>
 *  [sin(angle), cos(angle), 0, 0]<br>
 *  [0, 0, 1, 0]<br>
 *  [0, 0, 0, 1]<br>
 *
 * @param angle The angle in radians of type double
 *
 * @return The created rotation matrix
 */
Matrix4 Matrix4::createRotationZMatrix(const double angle)
{
    const auto cosAngleF = static_cast<float>(cos(angle));
    const auto sinAngleF = static_cast<float>(sin(angle));

    //@formatter:off
    return Matrix4({
        cosAngleF, -sinAngleF, 0, 0,
        sinAngleF,  cosAngleF, 0, 0,
                0,          0, 1, 0,
                0,          0, 0, 1
    });
    //@formatter:on
}

/**
 * Create a scaling matrix such as :<br>
 *  [sx, 0, 0, 0]<br>
 *  [0, sy, 0, 0]<br>
 *  [0, 0, sz, 0]<br>
 *  [0, 0, 0, 1 ]<br>
 *
 * @param sx The x translation
 * @param sy The y translation
 * @param sz The z translation
 *
 * @return The created scaling matrix
 */
Matrix4 Matrix4::createScalingMatrix(const float sx, const float sy, const float sz)
{
    //@formatter:off
    return Matrix4({
        sx,  0,  0, 0,
         0, sy,  0, 0,
         0,  0, sz, 0,
         0,  0,  0, 1
    });
    //@formatter:on
}

/**
 * Create a translation matrix such as :<br>
 *  [1, 0, 0, tx]<br>
 *  [0, 1, 0, ty]<br>
 *  [0, 0, 1, tz]<br>
 *  [0, 0, 0, 1 ]<br>
 *
 * @param tx The x translation
 * @param ty The y translation
 * @param tz The z translation
 *
 * @return The created translation matrix
 */
Matrix4 Matrix4::createTranslationMatrix(const float tx, const float ty, const float tz)
{
    //@formatter:off
    return Matrix4({
        1, 0, 0, tx,
        0, 1, 0, ty,
        0, 0, 1, tz,
        0, 0, 0, 1,
    });
    //@formatter:on
}

/**
 * @return A string containing the data of the matrix
 */
[[nodiscard]] std::string Matrix4::toString() const
{
    std::ostringstream oss;
    oss << "Matrix4("
            << "Row1: [" << _data[0] << ", " << _data[1] << ", " << _data[2] << ", " << _data[3] << "], "
            << "Row2: [" << _data[4] << ", " << _data[5] << ", " << _data[6] << ", " << _data[7] << "], "
            << "Row3: [" << _data[8] << ", " << _data[9] << ", " << _data[10] << ", " << _data[11] << "], "
            << "Row4: [" << _data[12] << ", " << _data[13] << ", " << _data[14] << ", " << _data[15] << "])";
    return oss.str();
}