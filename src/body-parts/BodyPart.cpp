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

    _startLinesVerticesBufferStartIndex = BufferManager::add(LINES_VERTICES, _linesVertices);
    _startLinesColorBufferStartIndex = BufferManager::add(LINES_COLORS, _linesColors);
    _startTrianglesVerticesBufferStartIndex = BufferManager::add(TRIANGLES_VERTICES, _trianglesVertices);
    _startTrianglesColorBufferStartIndex = BufferManager::add(TRIANGLES_COLORS, _trianglesColors);
    _updateVertices();
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
void BodyPart::removeChild(const BodyPart* child)
{
    std::erase(_children, child);
}

/**
 * Update the vertices of the body part.
 */
void BodyPart::_updateVertices()
{
    constexpr float cubeSize = 0.15f;
    const Matrix4 rotationMatrix = Matrix4::createRotationMatrix(_dir.getX(), _dir.getY(), _dir.getZ());

    Vector4 frontTopLeft = Vector4(-cubeSize, cubeSize, cubeSize);
    Vector4 frontTopRight = Vector4(cubeSize, cubeSize, cubeSize);
    Vector4 frontBottomLeft = Vector4(-cubeSize, -cubeSize, cubeSize);
    Vector4 frontBottomRight = Vector4(cubeSize, -cubeSize, cubeSize);

    Vector4 backTopLeft = Vector4(-cubeSize, cubeSize, -cubeSize);
    Vector4 backTopRight = Vector4(cubeSize, cubeSize, -cubeSize);
    Vector4 backBottomLeft = Vector4(-cubeSize, -cubeSize, -cubeSize);
    Vector4 backBottomRight = Vector4(cubeSize, -cubeSize, -cubeSize);

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
        // Front face
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),
        frontBottomRight.getX(), frontBottomRight.getY(), frontBottomRight.getZ(),
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        frontTopRight.getX(), frontTopRight.getY(), frontTopRight.getZ(),
        frontBottomRight.getX(), frontBottomRight.getY(), frontBottomRight.getZ(),

        // Back face
        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        backBottomLeft.getX(), backBottomLeft.getY(), backBottomLeft.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),
        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        backTopRight.getX(), backTopRight.getY(), backTopRight.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),

        // Left face
        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        backBottomLeft.getX(), backBottomLeft.getY(), backBottomLeft.getZ(),
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),
        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),

        // Right face
        frontTopRight.getX(), frontTopRight.getY(), frontTopRight.getZ(),
        frontBottomRight.getX(), frontBottomRight.getY(), frontBottomRight.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),
        frontTopRight.getX(), frontTopRight.getY(), frontTopRight.getZ(),
        backTopRight.getX(), backTopRight.getY(), backTopRight.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),

        // Top face
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        backTopLeft.getX(), backTopLeft.getY(), backTopLeft.getZ(),
        backTopRight.getX(), backTopRight.getY(), backTopRight.getZ(),
        frontTopLeft.getX(), frontTopLeft.getY(), frontTopLeft.getZ(),
        frontTopRight.getX(), frontTopRight.getY(), frontTopRight.getZ(),
        backTopRight.getX(), backTopRight.getY(), backTopRight.getZ(),

        // Bottom face
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),
        backBottomLeft.getX(), backBottomLeft.getY(), backBottomLeft.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ(),
        frontBottomLeft.getX(), frontBottomLeft.getY(), frontBottomLeft.getZ(),
        frontBottomRight.getX(), frontBottomRight.getY(), frontBottomRight.getZ(),
        backBottomRight.getX(), backBottomRight.getY(), backBottomRight.getZ()
    };

    _trianglesColors = {
        // Front face
        1.0f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f,

        // Back face
        0.3f, 1.0f, 0.3f,
        0.3f, 1.0f, 0.3f,
        0.3f, 1.0f, 0.3f,
        0.3f, 1.0f, 0.3f,
        0.3f, 1.0f, 0.3f,
        0.3f, 1.0f, 0.3f,

        // Left face
        0.3f, 0.3f, 1.0f,
        0.3f, 0.3f, 1.0f,
        0.3f, 0.3f, 1.0f,
        0.3f, 0.3f, 1.0f,
        0.3f, 0.3f, 1.0f,
        0.3f, 0.3f, 1.0f,

        // Right face
        1.0f, 1.0f, 0.3f,
        1.0f, 1.0f, 0.3f,
        1.0f, 1.0f, 0.3f,
        1.0f, 1.0f, 0.3f,
        1.0f, 1.0f, 0.3f,
        1.0f, 1.0f, 0.3f,

        // Top face
        1.0f, 0.3f, 1.0f,
        1.0f, 0.3f, 1.0f,
        1.0f, 0.3f, 1.0f,
        1.0f, 0.3f, 1.0f,
        1.0f, 0.3f, 1.0f,
        1.0f, 0.3f, 1.0f,

        // Bottom face
        0.3f, 1.0f, 1.0f,
        0.3f, 1.0f, 1.0f,
        0.3f, 1.0f, 1.0f,
        0.3f, 1.0f, 1.0f,
        0.3f, 1.0f, 1.0f,
        0.3f, 1.0f, 1.0f
    };
    //@formatter:on

    _startTrianglesVerticesBufferStartIndex = BufferManager::modify(TRIANGLES_VERTICES,
                                                                    _startTrianglesVerticesBufferStartIndex,
                                                                    _trianglesVertices);
    _startTrianglesColorBufferStartIndex = BufferManager::modify(TRIANGLES_COLORS,
                                                                 _startTrianglesColorBufferStartIndex,
                                                                 _trianglesColors);
}
