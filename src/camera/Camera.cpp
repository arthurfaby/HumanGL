#include "Camera.hpp"

#include <CameraDefines.hpp>
#include <cmath>
#include <MathsDefines.hpp>
#include <WindowDefines.hpp>

Camera* Camera::_instance = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Camera::Camera(const Vector4& position): _cameraPosition(position),
                                         _cameraFront(Vector4(0.0f, 0.0f, -1.0f)),
                                         _cameraUp(Vector4(0.0f, 1.0f, 0.0f)),
                                         _worldUp(Vector4(0.0f, 1.0f, 0.0f)),
                                         // @formatter:off
                                         _projectionMatrix(Matrix4({
                                             PROJECTION_FORMULA / ASPECT_RATIO, 0, 0, 0,
                                             0, PROJECTION_FORMULA, 0, 0,
                                             0, 0, (-FAR_PLANE_Z - NEAR_PLANE_Z)/Z_RANGE, (2 * FAR_PLANE_Z * NEAR_PLANE_Z)/Z_RANGE,
                                             0, 0, 1, 0,
                                         })),
                                         // @formatter:on
                                         _cameraXRotation(0.0f),
                                         _cameraYRotation(0.0f),
                                         _pitch(0.0f),
                                         _speed(0.015f),
                                         _yaw(-90.0f)
{
    _updateCameraVectors();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The unique instance of camera
 */
Camera& Camera::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Camera(Vector4(0.0, 0.0, 1.0));
    }
    return *_instance;
}

/**
 * @return The position of the camera
 */
const Vector4& Camera::getPosition() const
{
    return _cameraPosition;
}

/**
 * @return The projection matrix
 */
const Matrix4& Camera::getProjectionMatrix() const
{
    return _projectionMatrix;
}

/**
 * @return The x rotation value of the camera
 */
float Camera::getXRotation() const
{
    return _cameraXRotation;
}

/**
 * @return The y rotation value of the camera
 */
float Camera::getYRotation() const
{
    return _cameraYRotation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Modify x rotation value of the camera depending on the provided direction.
 *
 * @param dir The direction towards which the camera is going
 */
void Camera::setXRotation(const CameraDirection dir)
{
    switch (dir)
    {
        case UP:
            _cameraXRotation -= _speed;
            break;
        case DOWN:
            _cameraXRotation += _speed;
            break;
        default:
            break;
    }
}

/**
 * Modify y rotation value of the camera depending on the provided direction.
 *
 * @param dir The direction towards which the camera is going
 */
void Camera::setYRotation(const CameraDirection dir)
{
    switch (dir)
    {
        case LEFT:
            _cameraYRotation -= _speed;
            break;
        case RIGHT:
            _cameraYRotation += _speed;
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Update the position of the camera depending on the provided direction.
 *
 * @param dir The direction towards which the camera is going
 */
void Camera::updateCameraPos(const CameraDirection dir)
{
    switch (dir)
    {
        case FORWARD:
            _cameraPosition += _cameraFront * _speed;
            break;
        case BACKWARD:
            _cameraPosition -= _cameraFront * _speed;
            break;
        case RIGHT:
            _cameraPosition += _cameraRight * _speed;
            break;
        case LEFT:
            _cameraPosition -= _cameraRight * _speed;
            break;
        case UP:
            _cameraPosition += _cameraUp * _speed;
            break;
        case DOWN:
            _cameraPosition -= _cameraUp * _speed;
            break;
        case NONE:
            break;
    }
}

Matrix4 Camera::getFinalMatrix()
{
    const Matrix4 translationMatrix = Matrix4::createTranslationMatrix(
        getInstance().getPosition().getX(),
        getInstance().getPosition().getY(),
        getInstance().getPosition().getZ()
    );

    const Matrix4 rotationMatrix = Matrix4::createRotationYMatrix(-getInstance().getYRotation()) *
                                   Matrix4::createRotationXMatrix(-getInstance().getXRotation());

    return getInstance().getProjectionMatrix() * translationMatrix * rotationMatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Update the camera vectors so that the camera "looks" in front of it.
 */
void Camera::_updateCameraVectors()
{
    Vector4 direction;

    direction.setX(cosf(ToRadian(_yaw)) * cosf(ToRadian(_pitch)));
    direction.setY(sinf(ToRadian(_pitch)));
    direction.setZ(sinf(ToRadian(_yaw)) * cosf(ToRadian(_pitch)));
    direction.setW(0.0f);

    _cameraFront = direction.normalize();
    _cameraRight = _worldUp.cross(_cameraFront).normalize();
    _cameraUp = _cameraRight.cross(_cameraFront).normalize();
}