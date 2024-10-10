#include "Matrix4.hpp"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Construct a new Matrix4 object.
 *
 * @param newData An array of 16 float values to initialize the matrix with
 */
Matrix4::Matrix4(const float newData[16])
{
    for (int i = 0; i < 16; ++i)
    {
        _data[i] = newData[i];
    }
}

/**
 * @return The number of rows of the matrix
 */
[[nodiscard]] int Matrix4::getM() const
{
    return _m;
}

/**
 * @return The number of columns of the matrix
 */
[[nodiscard]] int Matrix4::getN() const
{
    return _n;
}

/**
 * Get the value at the specified row and column of the matrix.
 *
 * @param m The row of the matrix to access between 1 and 4
 * @param n The column of the matrix to access between 1 and 4
 *
 * @return The value at [m, n] in the matrix
 */
[[nodiscard]] float Matrix4::getValueAt(int m, int n) const
{
    m -= 1;
    n -= 1;

    if ((m < 0 || m > 3) || (n < 0 || n > 3))
    {
        throw std::out_of_range("Matrix index out of range");
    }
    return _data[m * 4 + n];
}

[[nodiscard]] float Matrix4::getMatrix(int) const
{
    return 0.0f;
}