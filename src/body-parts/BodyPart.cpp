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

    _trianglesColorsBuffer = _getTrianglesColorsBuffer();
    _trianglesVerticesBuffer = _getTrianglesVerticesBuffer();

    _trianglesVerticesBufferIndex = BufferManager::add(TRIANGLES_VERTICES, _trianglesVerticesBuffer);
    _trianglesColorsBufferIndex = BufferManager::add(TRIANGLES_COLORS, _trianglesColorsBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The matrix stack of the body part
 */
[[nodiscard]] Matrix4 BodyPart::getMatrixStack() const
{
    return _matrixStack.top();
}

[[nodiscard]] Matrix4 BodyPart::getScaleMatrix() const
{
    return _scaleMatrix;
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
    const Matrix4 ownShift = Matrix4::createTranslationMatrix(_ownRelativeShiftX,
                                                              _ownRelativeShiftY,
                                                              _ownRelativeShiftZ);
    const Matrix4 parentShift = Matrix4::createTranslationMatrix(_parentRelativeShiftX,
                                                                 _parentRelativeShiftY,
                                                                 _parentRelativeShiftZ);
    const Matrix4 combinedTransformation = ownShift * parentShift * _translationMatrix * _rotationMatrix;

    // Translation to bring back the object to its origin point
    const Matrix4 translationBackFromPivot = Matrix4::createTranslationMatrix(
        _pivotPoint.getX(),
        _pivotPoint.getY(),
        _pivotPoint.getZ());

    const Matrix4 transformMatrix = translationBackFromPivot * combinedTransformation * translationToPivot;

    return transformMatrix;
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

/**
 * Set the X angle of the body part.
 *
 * @param angle The new angle value
 *
 * @return itself
 */
BodyPart& BodyPart::setXRotation(const float angle)
{
    _angleX = angle;
    _rotationMatrix = Matrix4::createRotationMatrix(angle, _angleY, _angleZ);
    return *this;
}

/**
 * Set the Y angle of the body part.
 *
 * @param angle The new angle value
 *
 * @return itself
 */
BodyPart& BodyPart::setYRotation(const float angle)
{
    _angleY = angle;
    _rotationMatrix = Matrix4::createRotationMatrix(_angleX, angle, _angleZ);
    return *this;
}

/**
 * Set the Z angle of the body part.
 *
 * @param angle The new angle value
 *
 * @return itself
 */
BodyPart& BodyPart::setZRotation(const float angle)
{
    _angleZ = angle;
    _rotationMatrix = Matrix4::createRotationMatrix(_angleX, _angleY, angle);
    return *this;
}

/**
 * Set the X translation of the body part.
 *
 * @param x The new x value
 *
 * @return itself
 */
BodyPart& BodyPart::setTranslateX(const float x)
{
    _translateX = x;
    _translationMatrix = Matrix4::createTranslationMatrix(x, _translateY, _translateZ);
    return *this;
}

/**
 * Set the Y translation of the body part.
 *
 * @param y The new y value
 *
 * @return itself
 */
BodyPart& BodyPart::setTranslateY(const float y)
{
    _translateY = y;
    _translationMatrix = Matrix4::createTranslationMatrix(_translateX, y, _translateZ);
    return *this;
}

/**
 * Set the Z translation of the body part.
 *
 * @param z The new z value
 *
 * @return itself
 */
BodyPart& BodyPart::setTranslateZ(const float z)
{
    _translateZ = z;
    _translationMatrix = Matrix4::createTranslationMatrix(_translateX, _translateY, z);
    return *this;
}

/**
 * Set the parent relative shift of the body part.
 *
 * @param x The new x value
 * @param y The new y value
 * @param z The new z value
 *
 * @return itself
 */
BodyPart& BodyPart::setParentRelativeShift(const float x, const float y, const float z)
{
    _parentRelativeShiftX = x;
    _parentRelativeShiftY = y;
    _parentRelativeShiftZ = z;
    return *this;
}

/**
 * Set the own relative shift of the body part.
 *
 * @param x The new x value
 * @param y The new y value
 * @param z The new z value
 *
 * @return itself
 */
BodyPart& BodyPart::setOwnRelativeShift(const float x, const float y, const float z)
{
    _ownRelativeShiftX = x;
    _ownRelativeShiftY = y;
    _ownRelativeShiftZ = z;
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
    _angleX += angle;
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
    _angleY += angle;
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
    _angleZ += angle;
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
    _translateX += x;
    _translateY += y;
    _translateZ += z;
    _translationMatrix = _translationMatrix * Matrix4::createTranslationMatrix(x, y, z);
    return *this;
}

/**
  * Apply a scaling to the body part.
  *
  * @param x The x scale
  * @param y The y scale
  * @param z The z scale
  *
  * @return itself
  */
BodyPart& BodyPart::scale(const float x, const float y, const float z)
{
    _scaleMatrix = _scaleMatrix * Matrix4::createScalingMatrix(x, y, z);
    setOwnRelativeShift(_ownRelativeShiftX * x, _ownRelativeShiftY * y, _ownRelativeShiftZ * z);
    const Vector4 scaledPivotPoint = Vector4(_pivotPoint.getX() * x,
                                             _pivotPoint.getY() * y,
                                             _pivotPoint.getZ() * z,
                                             1.0f);
    setPivotPoint(scaledPivotPoint);
    for (auto& child: _children)
    {
        // Update translate to match the new scale
        child->setParentRelativeShift(child->_parentRelativeShiftX * x,
                                      child->_parentRelativeShiftY * y,
                                      child->_parentRelativeShiftZ * z);
    }
    return *this;
}

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
    const Vector4 scaleVector = _scaleMatrix * Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    float halfWidth = LENGTH_BASE_UNIT * scaleVector.getX() / 2.0f;
    float halfHeight = LENGTH_BASE_UNIT * scaleVector.getY() / 2.0f;
    float halfDepth = LENGTH_BASE_UNIT * scaleVector.getZ() / 2.0f;

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
