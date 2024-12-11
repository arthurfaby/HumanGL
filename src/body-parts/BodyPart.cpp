#include "BodyPart.hpp"

#include <BufferManager.hpp>
#include <Logger.hpp>

int BodyPart::_faceCount = 6;
int BodyPart::_verticesPerFace = 6;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BodyPart::BodyPart() : _rotationMatrix(Matrix4::identity()),
                       _translationMatrix(Matrix4::identity()),
                       _scaleMatrix(Matrix4::identity())
{
    _pivotPoint = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

    _linesColorsBuffer = _getLinesColorsBuffer();
    _linesVerticesBuffer = _getLinesVerticesBuffer();
    _trianglesColorsBuffer = _getTrianglesColorsBuffer();
    _trianglesVerticesBuffer = _getTrianglesVerticesBuffer();

    _linesVerticesBufferIndex = BufferManager::add(LINES_VERTICES, _linesVerticesBuffer);
    _linesColorsBufferIndex = BufferManager::add(LINES_COLORS, _linesColorsBuffer);
    _trianglesVerticesBufferIndex = BufferManager::add(TRIANGLES_VERTICES, _trianglesVerticesBuffer);
    _trianglesColorsBufferIndex = BufferManager::add(TRIANGLES_COLORS, _trianglesColorsBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The depth of the body part
 */
[[nodiscard]] float BodyPart::getDepth() const
{
    return _depth;
}

/**
 * @return The height of the body part
 */
[[nodiscard]] float BodyPart::getHeight() const
{
    return _height;
}

/**
 * @return The width of the body part
 */
[[nodiscard]] float BodyPart::getWidth() const
{
    return _width;
}

/**
 * @return The matrix stack of the body part
 */
[[nodiscard]] Matrix4 BodyPart::getMatrixStack() const
{
    return _matrixStack.top();
}

/**
 * @return The transformation matrix of the body part
 */
[[nodiscard]] Matrix4 BodyPart::getTransformationMatrix() const
{
    // Translation to bring the object to the pivot point
    const Matrix4 translationToPivot = Matrix4::createTranslationMatrix(-_pivotPoint.getX(),
                                                                        -_pivotPoint.getY(),
                                                                        -_pivotPoint.getZ());

    // Apply all transformation : translation, rotation, etc.
    const Matrix4 combinedTransformation = _translationMatrix * _rotationMatrix;

    // Translation to bring back the object to its origin point
    const Matrix4 translationBackFromPivot = Matrix4::createTranslationMatrix(
        _pivotPoint.getX(),
        _pivotPoint.getY(),
        _pivotPoint.getZ());

    return translationBackFromPivot * combinedTransformation * translationToPivot;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Set the color of the body part using RGB values.
 *
 * @param red   The new red value
 * @param green The new green value
 * @param blue  The new blue value
 *
 * @return itself
 */
BodyPart& BodyPart::setColor(const float red, const float green, const float blue)
{
    _red = red;
    _green = green;
    _blue = blue;
    return *this;
}

/**
 * Set the depth of the body part.
 *
 * @param depth The new depth value
 *
 * @return itself
 */
BodyPart& BodyPart::setDepth(const float depth)
{
    this->_depth = depth;
    return *this;
}

/**
 * Set the height of the body part.
 *
 * @param height The new height value
 *
 * @return itself
 */
BodyPart& BodyPart::setHeight(const float height)
{
    this->_height = height;
    return *this;
}

/**
 * Set the width of the body part.
 *
 * @param width The new width value
 *
 * @return itself
 */
BodyPart& BodyPart::setWidth(const float width)
{
    this->_width = width;
    return *this;
}

/**
 * Set the parent of the body part.
 *
 * @param parent The new parent value
 *
 * @return itself
 */
BodyPart& BodyPart::setParent(BodyPart* parent)
{
    _parent = parent;
    return *this;
}

/**
 * Set the pivot point of the body part.
 *
 * @param pivotPoint The new pivot point value
 *
 * @return itself
 */
BodyPart& BodyPart::setPivotPoint(const Vector4& pivotPoint)
{
    _pivotPoint = pivotPoint;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Apply a rotation on the x-axis to the body part.
 *
 * @param angle The angle in radians to apply
 *
 * @return itself
 */
BodyPart& BodyPart::rotateX(const float angle)
{
    _rotationMatrix = _rotationMatrix * Matrix4::createRotationXMatrix(angle);
    return *this;
}

/**
 * Apply a rotation on the y-axis to the body part.
 *
 * @param angle The angle in radians to apply
 *
 * @return itself
 */
BodyPart& BodyPart::rotateY(const float angle)
{
    _rotationMatrix = _rotationMatrix * Matrix4::createRotationYMatrix(angle);
    return *this;
}

/**
 * Apply a rotation on the z-axis to the body part.
 *
 * @param angle The angle in radians to apply
 *
 * @return itself
 */
BodyPart& BodyPart::rotateZ(const float angle)
{
    _rotationMatrix = _rotationMatrix * Matrix4::createRotationZMatrix(angle);
    return *this;
}

/**
 * Apply a translation to the body part.
 *
 * @param x The x translation
 * @param y The y translation
 * @param z The z translation
 *
 * @return itself
 */
BodyPart& BodyPart::translate(const float x, const float y, const float z)
{
    if (_parent)
    {
        Logger::warning("Cannot translate an axis that has a parent.");
        return *this;
    }
    _translationMatrix = _translationMatrix * Matrix4::createTranslationMatrix(x, y, z);
    return *this;
}

// /**
//  * Apply a scaling to the body part.
//  *
//  * @param x The x scale
//  * @param y The y scale
//  * @param z The z scale
//  *
//  * @return itself
//  */
// BodyPart& BodyPart::scale(const float x, const float y, const float z)
// {
//     _scaleMatrix = _scaleMatrix * Matrix4::createScalingMatrix(x, y, z);
//     return *this;
// }

/**
 * Add a child to the body part.
 *
 * @param child The child to add
 *
 * @return itself
 */
BodyPart& BodyPart::addChild(BodyPart* child)
{
    _children.push_back(child);
    child->setParent(this);
    return *this;
}

/**
 * Apply all transformation to the body part.
 */
void BodyPart::applyTransformation()
{
    // If node does not have a parent, it is the target axis so it must not go through any additional transformation
    const Matrix4 parentMatrix = this->_parent ? this->_parent->getMatrixStack() : Matrix4::identity();
    const Matrix4 ownMatrix = parentMatrix * getTransformationMatrix();

    _matrixStack.push(ownMatrix);

    for (BodyPart* child: _children)
    {
        child->applyTransformation();
    }

    _linesVerticesBuffer = _getLinesVerticesBuffer();

    for (int i = 0; i < _linesVerticesBuffer.size(); i += 3)
    {
        const float x = _linesVerticesBuffer[i + 0];
        const float y = _linesVerticesBuffer[i + 1];
        const float z = _linesVerticesBuffer[i + 2];
        Vector4 vertex = Vector4(x, y, z, 1.0f);
        vertex = _matrixStack.top() * vertex;
        _linesVerticesBuffer[i + 0] = vertex.getX();
        _linesVerticesBuffer[i + 1] = vertex.getY();
        _linesVerticesBuffer[i + 2] = vertex.getZ();
    }

    // Draw the cube
    _trianglesVerticesBuffer = _getTrianglesVerticesBuffer();
    for (int i = 0; i < _trianglesVerticesBuffer.size(); i += 3)
    {
        const float x = _trianglesVerticesBuffer[i + 0];
        const float y = _trianglesVerticesBuffer[i + 1];
        const float z = _trianglesVerticesBuffer[i + 2];
        Vector4 vertex = Vector4(x, y, z, 1.0f);
        vertex = _matrixStack.top() * vertex;
        // vertex = _scaleMatrix * vertex;
        _trianglesVerticesBuffer[i + 0] = vertex.getX();
        _trianglesVerticesBuffer[i + 1] = vertex.getY();
        _trianglesVerticesBuffer[i + 2] = vertex.getZ();
    }
    _trianglesColorsBuffer = _getTrianglesColorsBuffer();

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

    _matrixStack.pop();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The buffer containing all the triangles vertices
 */
std::vector<float> BodyPart::_getTrianglesVerticesBuffer() const
{
    float halfWidth = _width / 2.0f;
    float halfHeight = _height / 2.0f;
    float halfDepth = _depth / 2.0f;

    //@formatter:off
    return {
        // Face avant
        -halfWidth, -halfHeight, halfDepth,
         halfWidth, -halfHeight, halfDepth,
         halfWidth,  halfHeight, halfDepth,
        -halfWidth, -halfHeight, halfDepth,
         halfWidth,  halfHeight, halfDepth,
        -halfWidth,  halfHeight, halfDepth,

        // Face arrière
        -halfWidth, -halfHeight, -halfDepth,
        -halfWidth,  halfHeight, -halfDepth,
         halfWidth,  halfHeight, -halfDepth,
        -halfWidth, -halfHeight, -halfDepth,
         halfWidth,  halfHeight, -halfDepth,
         halfWidth, -halfHeight, -halfDepth,

        // Face gauche
        -halfWidth, -halfHeight, -halfDepth,
        -halfWidth, -halfHeight,  halfDepth,
        -halfWidth,  halfHeight,  halfDepth,
        -halfWidth, -halfHeight, -halfDepth,
        -halfWidth,  halfHeight,  halfDepth,
        -halfWidth,  halfHeight, -halfDepth,

        // Face droite
         halfWidth, -halfHeight, -halfDepth,
         halfWidth,  halfHeight, -halfDepth,
         halfWidth,  halfHeight,  halfDepth,
         halfWidth, -halfHeight, -halfDepth,
         halfWidth,  halfHeight,  halfDepth,
         halfWidth, -halfHeight,  halfDepth,

        // Face supérieure
        -halfWidth,  halfHeight, -halfDepth,
        -halfWidth,  halfHeight,  halfDepth,
         halfWidth,  halfHeight,  halfDepth,
        -halfWidth,  halfHeight, -halfDepth,
         halfWidth,  halfHeight,  halfDepth,
         halfWidth,  halfHeight, -halfDepth,

        // Face inférieure
        -halfWidth, -halfHeight, -halfDepth,
         halfWidth, -halfHeight, -halfDepth,
         halfWidth, -halfHeight,  halfDepth,
        -halfWidth, -halfHeight, -halfDepth,
         halfWidth, -halfHeight,  halfDepth,
        -halfWidth, -halfHeight,  halfDepth
    };
    //@formatter:on
}

/**
 * @return The buffer containing all the triangles colors
 */
std::vector<float> BodyPart::_getTrianglesColorsBuffer() const
{
    const auto nbLoops = _faceCount * _verticesPerFace;

    std::vector<float> colors;
    for (int i = 0; i < nbLoops; i++)
    {
        colors.push_back(_red / 255.0f);
        colors.push_back(_green / 255.0f);
        colors.push_back(_blue / 255.0f);
    }
    return colors;
}

/**
 * @return The buffer containing all the lines vertices
 */
std::vector<float> BodyPart::_getLinesVerticesBuffer()
{
    //@formatter:off
    return {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f
    };
    //@formatter:on
}

/**
 * @return The buffer containing all the lines colors
 */
std::vector<float> BodyPart::_getLinesColorsBuffer()
{
    //@formatter:off
    return {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };
    //@formatter:on
}