#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <cmath>
#include <Matrix4.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Constructor.
 *
 * @param position The position of the body part
 */
BodyPart::BodyPart(const Vector4& position)
{
    _position = position;

    _startLinesVerticesBufferStartIndex = BufferManager::addLinesVertices(_linesVertices);
    _startLinesColorBufferStartIndex = BufferManager::addLinesColors(_linesColors);
    _startTrianglesVerticesBufferStartIndex = BufferManager::addTrianglesVertices(_trianglesVertices);
    _startTrianglesColorBufferStartIndex = BufferManager::addTrianglesColors(_trianglesColors);
    _updateVertices(false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The position of the body part
 */
[[nodiscard]] Vector4 BodyPart::getPosition() const
{
    return _position;
}

/**
 * @return The direction of the body part
 */
[[nodiscard]] Vector4 BodyPart::getDir() const
{
    return _dir;
}

/**
 * @return The children of the body part
 */
[[nodiscard]] std::vector<BodyPart*> BodyPart::getChildren() const
{
    return _children;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Set the position of the body part.
 *
 * @param position The new position of the body part.
 */
void BodyPart::setPosition(const Vector4& position)
{
    _position = position;
    _updateVertices();
}

/**
 * Set the direction of the body part.
 *
 * @param dir The new position of the body part.
 */
void BodyPart::setDir(const Vector4& dir)
{
    constexpr float pi = std::numbers::pi;
    _dir.setX(fmodf(dir.getX() + pi, 2 * pi) - pi);
    _dir.setY(fmodf(dir.getY() + pi, 2 * pi) - pi);
    _dir.setZ(fmodf(dir.getZ() + pi, 2 * pi) - pi);
    _updateVertices();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Add a child to the body part.
 *
 * @param child The child to add
 */
void BodyPart::addChild(BodyPart* child)
{
    _children.push_back(child);
}

/**
 * Remove a child from the body part.
 *
 * @param child The child to remove
 */
void BodyPart::removeChild(BodyPart* child)
{
    std::erase(_children, child);
}

/**
 * Update the vertices of the body part.
 *
 * @param modifyBuffer If true, the buffer will be modified
 */
void BodyPart::_updateVertices(bool modifyBuffer /*= true*/)
{
    float cubeSize = 0.15f;
    Matrix4 rotationMatrix = Matrix4::createRotationMatrix(_dir.getX(), _dir.getY(), _dir.getZ());

    Vector4 frontTopLeft = Vector4(-cubeSize, cubeSize, cubeSize, 1.0f);
    Vector4 frontTopRight = Vector4(cubeSize, cubeSize, cubeSize, 1.0f);
    Vector4 frontBottomLeft = Vector4(-cubeSize, -cubeSize, cubeSize, 1.0f);
    Vector4 frontBottomRight = Vector4(cubeSize, -cubeSize, cubeSize, 1.0f);

    Vector4 backTopLeft = Vector4(-cubeSize, cubeSize, -cubeSize, 1.0f);
    Vector4 backTopRight = Vector4(cubeSize, cubeSize, -cubeSize, 1.0f);
    Vector4 backBottomLeft = Vector4(-cubeSize, -cubeSize, -cubeSize, 1.0f);
    Vector4 backBottomRight = Vector4(cubeSize, -cubeSize, -cubeSize, 1.0f);

    frontTopLeft = rotationMatrix * frontTopLeft + _position;
    frontTopRight = rotationMatrix * frontTopRight + _position;
    frontBottomLeft = rotationMatrix * frontBottomLeft + _position;
    frontBottomRight = rotationMatrix * frontBottomRight + _position;

    backTopLeft = rotationMatrix * backTopLeft + _position;
    backTopRight = rotationMatrix * backTopRight + _position;
    backBottomLeft = rotationMatrix * backBottomLeft + _position;
    backBottomRight = rotationMatrix * backBottomRight + _position;

    //@formatter:off
    _trianglesVertices = {
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),
        frontBottomRight.getX(), frontBottomRight.getY(), frontBottomRight.getZ(),
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        frontTopRight.getX(), frontTopRight.getY(), frontTopRight.getZ(),
        frontBottomRight.getX(), frontBottomRight.getY(), frontBottomRight.getZ(),

        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        backBottomLeft.getX(), backBottomLeft.getY(), backBottomLeft.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),
        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        backTopRight.getX(), backTopRight.getY(), backTopRight.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),

        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        backBottomLeft.getX(), backBottomLeft.getY(), backBottomLeft.getZ(),
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),
        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),

        frontTopRight.getX(), frontTopRight.getY(), frontTopRight.getZ(),
        frontBottomRight.getX(), frontBottomRight.getY(), frontBottomRight.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),
        frontTopRight.getX(), frontTopRight.getY(), frontTopRight.getZ(),
        backTopRight.getX(), backTopRight.getY(), backTopRight.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),

        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        backTopRight.getX(), backTopRight.getY(), backTopRight.getZ(),
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        frontTopRight.getX(), frontTopRight.getY(), frontTopRight.getZ(),
        backTopRight.getX(), backTopRight.getY(), backTopRight.getZ(),

        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),
        backBottomLeft.getX(), backBottomLeft.getY(), backBottomLeft.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),
        frontBottomRight.getX(), frontBottomRight.getY(), frontBottomRight.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ()
    };

    _trianglesColors = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f
    };
    //@formatter:on

    _startTrianglesVerticesBufferStartIndex = BufferManager::modifyTrianglesVertices(
        _startTrianglesVerticesBufferStartIndex,
        _trianglesVertices);
    _startTrianglesColorBufferStartIndex = BufferManager::modifyTrianglesColors(
        _startTrianglesColorBufferStartIndex,
        _trianglesColors);
}
