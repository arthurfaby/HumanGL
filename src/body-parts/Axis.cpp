// Axis.cpp
#include "Axis.hpp"

#include <BufferManager.hpp>
#include <Logger.hpp>
#include <MatrixStack.hpp>

Axis::Axis() : _translationMatrix(Matrix4::identity()), _rotationMatrix(Matrix4::identity())
{
    _pivotPoint = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    _linesVerticesBufferIndex = BufferManager::add(LINES_VERTICES, _linesVerticesBuffer);
    _linesColorsBufferIndex = BufferManager::add(LINES_COLORS, _linesColorsBuffer);
    _trianglesVerticesBufferIndex = BufferManager::add(TRIANGLES_VERTICES, _trianglesVerticesBuffer);
    _trianglesColorsBufferIndex = BufferManager::add(TRIANGLES_COLORS, _trianglesColorsBuffer);
    draw();
}

void Axis::translate(const float x, const float y, const float z)
{
    Matrix4 translation = Matrix4::createTranslationMatrix(x, y, z);
    _translationMatrix = _translationMatrix * translation;
}

void Axis::rotateX(const float angle)
{
    _rotationMatrix = _rotationMatrix * Matrix4::createRotationXMatrix(angle);
}

void Axis::rotateY(const float angle)
{
    _rotationMatrix = _rotationMatrix * Matrix4::createRotationYMatrix(angle);
}

void Axis::rotateZ(const float angle)
{
    _rotationMatrix = _rotationMatrix * Matrix4::createRotationZMatrix(angle);
}

void Axis::addChild(Axis* child)
{
    _children.push_back(child);
    draw();
}

Matrix4 Axis::getTransformationMatrix() const
{
    // 1. Translation pour amener l'objet au point d'attache
    const Matrix4 translationToPivot = Matrix4::createTranslationMatrix(-_pivotPoint.getX(),
                                                                        -_pivotPoint.getY(),
                                                                        -_pivotPoint.getZ());

    // 2. Appliquer les transformations : translation, rotation, etc.
    const Matrix4 combinedTransformation = _translationMatrix * _rotationMatrix;

    // 3. Retourner l'objet à sa position d'origine après transformation
    const Matrix4 translationBackFromPivot = Matrix4::createTranslationMatrix(
        _pivotPoint.getX(),
        _pivotPoint.getY(),
        _pivotPoint.getZ());

    // Combiner tout
    return translationBackFromPivot * combinedTransformation * translationToPivot;
}

void Axis::setPivotPoint(const Vector4& pivotPoint)
{
    _pivotPoint = pivotPoint;
}

void Axis::draw()
{
    for (Axis* child: _children)
    {
        child->draw();
    }
    MatrixStack::push(getTransformationMatrix());
    constexpr float CUBE_SIZE = 0.1f;

    //@formatter:off
    _linesVerticesBuffer = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f
    };

    _linesColorsBuffer = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    // Draw the cube
    _trianglesVerticesBuffer = {
        // Front face
        -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
        CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        // Back face
        -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
        -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        // Left face
        -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
        -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
        // Right face
        CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
        // Top face
        -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
        -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, CUBE_SIZE,
        CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
        // Bottom face
        -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
        -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
        CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
        -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE
        };

    _trianglesColorsBuffer = {
        // Front face
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Back face
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        // Left face
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Right face
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        // Top face
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        // Bottom face
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f
    };

    //@formatter:on
    _trianglesVerticesBufferIndex = BufferManager::modify(TRIANGLES_VERTICES,
                                                          _trianglesVerticesBufferIndex,
                                                          _trianglesVerticesBuffer);
    _trianglesColorsBufferIndex = BufferManager::modify(TRIANGLES_COLORS,
                                                        _trianglesColorsBufferIndex,
                                                        _trianglesColorsBuffer);
    _linesVerticesBufferIndex = BufferManager::modify(LINES_VERTICES,
                                                      _linesVerticesBufferIndex,
                                                      _linesVerticesBuffer);
    _linesColorsBufferIndex = BufferManager::modify(LINES_COLORS, _linesColorsBufferIndex, _linesColorsBuffer);

    MatrixStack::pop();
}
