#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <cmath>
#include <iostream>
#include <Logger.hpp>
#include <Matrix4.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Constructor.
 *
 * @param position The position of the body part
 * @param offset
 */
BodyPart::BodyPart(const Vector4& position, const Vector4& offset)
{
    _position = position;
    _offset = offset;

    _startLinesVerticesBufferStartIndex = BufferManager::addLinesVertices(_linesVertices);
    _startLinesColorBufferStartIndex = BufferManager::addLinesColors(_linesColors);
    _startTrianglesVerticesBufferStartIndex = BufferManager::addTrianglesVertices(_trianglesVertices);
    _startTrianglesColorBufferStartIndex = BufferManager::addTrianglesColors(_trianglesColors);
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
 * @return The direction of the body part
 */
[[nodiscard]] Vector4 BodyPart::getDir() const
{
    return _dir;
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
 * Get the rotation matrix of the body part.
 *
 * @return The rotation matrix of the body part
 */
[[nodiscard]] Matrix4 BodyPart::getRotationMatrix() const
{
    const Matrix4 rotationX = Matrix4::createRotationXMatrix(_dir.getX());
    const Matrix4 rotationY = Matrix4::createRotationYMatrix(_dir.getY());
    const Matrix4 rotationZ = Matrix4::createRotationZMatrix(_dir.getZ());

    return rotationZ * rotationY * rotationX;
}

/**
 * Add a child to the body part.
 *
 * @param child The child to add
 */
void BodyPart::addChild(BodyPart* child)
{
    _children.push_back(child);
    child->setParent(this);
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
}

/**
 * Update the vertices of the body part.
 */
void BodyPart::updateVertices()
{
    static bool a = false;
    float cubeSize = 0.15f;
    Matrix4 rotationMatrix = getRotationMatrix(); // Utiliser la matrice de rotation

    Vector4 frontTopLeft = Vector4(-cubeSize, cubeSize, cubeSize, 1.0f);
    Vector4 frontTopRight = Vector4(cubeSize, cubeSize, cubeSize, 1.0f);
    Vector4 frontBottomLeft = Vector4(-cubeSize, -cubeSize, cubeSize, 1.0f);
    Vector4 frontBottomRight = Vector4(cubeSize, -cubeSize, cubeSize, 1.0f);

    Vector4 backTopLeft = Vector4(-cubeSize, cubeSize, -cubeSize, 1.0f);
    Vector4 backTopRight = Vector4(cubeSize, cubeSize, -cubeSize, 1.0f);
    Vector4 backBottomLeft = Vector4(-cubeSize, -cubeSize, -cubeSize, 1.0f);
    Vector4 backBottomRight = Vector4(cubeSize, -cubeSize, -cubeSize, 1.0f);

    Matrix4 scaleMatrix = Matrix4::createScalingMatrix(0.5f, 0.5f, 0.5f);
    if (!a)
    {
        Logger::error("toto");
        Vector4 newOffset = _offset;
        _offset.setX(_offset.getX() * 0.5f);
        _offset.setY(_offset.getY() * 0.5f);
        _offset.setZ(_offset.getZ() * 0.5f);
        a = true;
    }

    frontTopLeft = rotationMatrix * scaleMatrix * frontTopLeft + _position;
    frontTopRight = rotationMatrix * scaleMatrix * frontTopRight + _position;
    frontBottomLeft = rotationMatrix * scaleMatrix * frontBottomLeft + _position;
    frontBottomRight = rotationMatrix * scaleMatrix * frontBottomRight + _position;

    backTopLeft = rotationMatrix * scaleMatrix * backTopLeft + _position;
    backTopRight = rotationMatrix * scaleMatrix * backTopRight + _position;
    backBottomLeft = rotationMatrix * scaleMatrix * backBottomLeft + _position;
    backBottomRight = rotationMatrix * scaleMatrix * backBottomRight + _position;

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

    for (const auto& child: _children)
    {
        child->setDir(getDir()); // Applique la rotation au child

        // Utilisez la matrice de rotation du parent pour le calcul de la position
        Vector4 childLocalPosition = child->getOffset(); // Utilise l'offset pour la position locale
        Vector4 newChildPosition = rotationMatrix * childLocalPosition + _position; // Calcul de la nouvelle position
        child->setPosition(newChildPosition); // Met à jour la position de l'enfant
    }
}
