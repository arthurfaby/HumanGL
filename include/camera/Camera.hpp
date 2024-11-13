#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Matrix4.hpp>
#include <Vector4.hpp>

enum CameraDirection
{
    NONE = 0,
    FORWARD = 1,
    BACKWARD = 2,
    LEFT = 3,
    RIGHT = 4,
    UP = 5,
    DOWN = 6
};

class Camera
{
public:
    // Constructors
    Camera() = delete;
    Camera(const Camera& other) = delete;

    // Destructor
    ~Camera() = default;

    // Getters
    [[nodiscard]] static Camera& getInstance();
    [[nodiscard]] const Vector4& getPosition() const;
    [[nodiscard]] const Matrix4& getProjectionMatrix() const;
    [[nodiscard]] float getXRotation() const;
    [[nodiscard]] float getYRotation() const;

    // Setters
    void setXRotation(CameraDirection dir);
    void setYRotation(CameraDirection dir);

    // Methods
    void updateCameraPos(CameraDirection dir);

private:
    explicit Camera(const Vector4& position);

    static Camera* _instance;

    Vector4 _cameraPosition;
    Vector4 _cameraFront;
    Vector4 _cameraUp;
    Vector4 _cameraRight;
    Vector4 _worldUp;

    Matrix4 _projectionMatrix;

    float _cameraXRotation;
    float _cameraYRotation;
    float _pitch;
    float _speed;
    float _yaw;

    // Methods
    void _updateCameraVectors();
};

#endif //CAMERA_HPP