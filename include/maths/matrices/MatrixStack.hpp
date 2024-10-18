#ifndef MATRIX_STACK_HPP
#define MATRIX_STACK_HPP
#include <Matrix4.hpp>
#include <vector>

class MatrixStack
{
public:
    // Constructors
    MatrixStack() = delete;
    MatrixStack(const MatrixStack& other) = delete;

    // Destructor
    ~MatrixStack() = delete;

    // Operator overloads
    MatrixStack& operator=(const MatrixStack& other) = delete;

    // Methods
    static void push(const Matrix4& matrix);
    static Matrix4 pop();
    static void clear();
    static Matrix4 top();
    static std::vector<Matrix4> data();

private:
    /**
     * The stack of matrices.
     */
    static std::vector<Matrix4> _data;
};

#endif //MATRIX_STACK_HPP
