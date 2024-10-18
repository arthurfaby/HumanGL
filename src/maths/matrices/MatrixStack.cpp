#include "MatrixStack.hpp"
#include <Logger.hpp>

std::vector<Matrix4> MatrixStack::_data;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Push a matrix to the stack.
 *
 * @param matrix The matrix to push.
 */
void MatrixStack::push(const Matrix4& matrix)
{
    _data.push_back(matrix);
}

/**
 * Pop a matrix from the stack.
 *
 * @return The matrix that has been popped.
 */
Matrix4 MatrixStack::pop()
{
    if (_data.empty())
    {
        Logger::warning("MatrixStack::pop(): Stack is empty.");
        return Matrix4::identity();
    }
    Matrix4 matrix = _data.back();
    _data.pop_back();
    return matrix;
}

/**
 * Clear the stack.
 */
void MatrixStack::clear()
{
    _data.clear();
}

/**
 * Get the top matrix of the stack.
 *
 * @return The top matrix of the stack.
 */
Matrix4 MatrixStack::top()
{
    if (_data.empty())
    {
        Logger::warning("MatrixStack::top(): Stack is empty.");
        return Matrix4::identity();
    }
    return _data.back();
}

/**
 * Get the data of the stack.
 *
 * @return The data of the stack.
 */
std::vector<Matrix4> MatrixStack::data()
{
    return _data;
}
