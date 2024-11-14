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
 * @param offset The offset of the body part
 */
BodyPart::BodyPart(const Vector4& position, const Vector4& offset)
{
    _position = position;
    _offset = offset;

    _startLinesVerticesBufferStartIndex = BufferManager::add(LINES_VERTICES, _linesVertices);
    _startLinesColorBufferStartIndex = BufferManager::add(LINES_COLORS, _linesColors);
    _startTrianglesVerticesBufferStartIndex = BufferManager::add(TRIANGLES_VERTICES, _trianglesVertices);
    _startTrianglesColorBufferStartIndex = BufferManager::add(TRIANGLES_COLORS, _trianglesColors);
    updateVertices();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The offset of the body part
 */
[[nodiscard]] Vector4 BodyPart::getOffset() const
{
    return _offset;
}

/**
 * @return The position of the body part
 */
[[nodiscard]] Vector4 BodyPart::getPosition() const
{
    return _position;
}

/**
 * @return The angle on the X axis of the body part
 */
[[nodiscard]] double BodyPart::getAngleX() const
{
    return _angleX;
}

/**
 * @return The angle on the Y axis of the body part
 */
[[nodiscard]] double BodyPart::getAngleY() const
{
    return _angleY;
}

/**
 * @return The angle on the Z axis of the body part
 */
[[nodiscard]] double BodyPart::getAngleZ() const
{
    return _angleZ;
}

/**
 * @return The parent of the body part
 */
[[nodiscard]] BodyPart* BodyPart::getParent() const
{
    return _parent;
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
 * Set the offset of the body part.
 *
 * @param offset The new offset of the body part
 */
void BodyPart::setOffset(const Vector4& offset)
{
    _offset = offset;
    updateVertices();
}

/**
 * Set the position of the body part.
 *
 * @param position The new position of the body part.
 */
void BodyPart::setPosition(const Vector4& position)
{
    _position = position;
    updateVertices();
}

/**
 * Set the angle on the X axis of the body part.
 *
 * @param angleX The new angle on the X axis of the body part
 */
void BodyPart::setAngleX(const double angleX)
{
    _angleX = fmod(angleX + std::numbers::pi, 2 * std::numbers::pi) - std::numbers::pi;
    updateVertices();
}

/**
 * Set the angle on the Y axis of the body part.
 *
 * @param angleY The new angle on the Y axis of the body part
 */
void BodyPart::setAngleY(const double angleY)
{
    _angleY = fmod(angleY + std::numbers::pi, 2 * std::numbers::pi) - std::numbers::pi;;
    updateVertices();
}

/**
 * Set the angle on the Z axis of the body part.
 *
 * @param angleZ The new angle on the Z axis of the body part
 */
void BodyPart::setAngleZ(const double angleZ)
{
    _angleZ = fmod(angleZ + std::numbers::pi, 2 * std::numbers::pi) - std::numbers::pi;;
    updateVertices();
}

/**
 * Set the parent of the body part.
 *
 * @param parent The new parent of the body part
 */
void BodyPart::setParent(BodyPart* parent)
{
    _parent = parent;
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
    child->setParent(this);
    updateVertices();
}

/**
 * Remove a child from the body part.
 *
 * @param child The child to remove
 */
void BodyPart::removeChild(BodyPart* child)
{
    std::erase(_children, child);
    child->setParent(nullptr);
    updateVertices();
}

/**
 * Update the vertices of the body part.
 */
void BodyPart::updateVertices()
{
    constexpr float cubeHalfEdge = 0.25f;
    const Matrix4 rotationMatrix = Matrix4::createRotationMatrix(_dir.getX(), _dir.getY(), _dir.getZ());

    Vector4 frontTopLeft = Vector4(-cubeHalfEdge, cubeHalfEdge, cubeHalfEdge);
    Vector4 frontTopRight = Vector4(cubeHalfEdge, cubeHalfEdge, cubeHalfEdge);
    Vector4 frontBottomLeft = Vector4(-cubeHalfEdge, -cubeHalfEdge, cubeHalfEdge);
    Vector4 frontBottomRight = Vector4(cubeHalfEdge, -cubeHalfEdge, cubeHalfEdge);

    Vector4 backTopLeft = Vector4(-cubeHalfEdge, cubeHalfEdge, -cubeHalfEdge);
    Vector4 backTopRight = Vector4(cubeHalfEdge, cubeHalfEdge, -cubeHalfEdge);
    Vector4 backBottomLeft = Vector4(-cubeHalfEdge, -cubeHalfEdge, -cubeHalfEdge);
    Vector4 backBottomRight = Vector4(cubeHalfEdge, -cubeHalfEdge, -cubeHalfEdge);

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
        0.8f, 0.3f, 0.3f,
        1.0f, 0.3f, 0.3f,
        0.8f, 0.3f, 0.3f,
        0.8f, 0.3f, 0.3f,

        // Back face
        0.3f, 1.0f, 0.3f,
        0.3f, 1.0f, 0.3f,
        0.3f, 0.8f, 0.3f,
        0.3f, 1.0f, 0.3f,
        0.3f, 0.8f, 0.3f,
        0.3f, 0.8f, 0.3f,

        // Left face
        0.3f, 0.3f, 1.0f,
        0.3f, 0.3f, 1.0f,
        0.3f, 0.3f, 0.8f,
        0.3f, 0.3f, 1.0f,
        0.3f, 0.3f, 0.8f,
        0.3f, 0.3f, 0.8f,

        // Right face
        1.0f, 1.0f, 0.3f,
        1.0f, 1.0f, 0.3f,
        0.8f, 0.8f, 0.3f,
        1.0f, 1.0f, 0.3f,
        0.8f, 0.8f, 0.3f,
        0.8f, 0.8f, 0.3f,

        // Top face
        1.0f, 0.3f, 1.0f,
        1.0f, 0.3f, 1.0f,
        0.8f, 0.3f, 0.8f,
        1.0f, 0.3f, 1.0f,
        0.8f, 0.3f, 0.8f,
        0.8f, 0.3f, 0.8f,

        // Bottom face
        0.3f, 1.0f, 1.0f,
        0.3f, 1.0f, 1.0f,
        0.3f, 0.8f, 0.8f,
        0.3f, 1.0f, 1.0f,
        0.3f, 0.8f, 0.8f,
        0.3f, 0.8f, 0.8f
    };
    //@formatter:on

    _startTrianglesVerticesBufferStartIndex = BufferManager::modify(TRIANGLES_VERTICES,
                                                                    _startTrianglesVerticesBufferStartIndex,
                                                                    _trianglesVertices);
    _startTrianglesColorBufferStartIndex = BufferManager::modify(TRIANGLES_COLORS,
                                                                 _startTrianglesColorBufferStartIndex,
                                                                 _trianglesColors);
    for (const auto& child: _children)
    {
        child->setAngleX(getAngleX());
        child->setAngleY(getAngleY());
        child->setAngleZ(getAngleZ());
        Vector4 childLocalPosition = child->getOffset();
        Vector4 newChildPosition = rotationMatrix * childLocalPosition + _position;
        child->setPosition(newChildPosition);
    }
}