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
    static void deleteCamera();
    [[nodiscard]] const Vector4& getPosition() const;
    [[nodiscard]] const Matrix4& getProjectionMatrix() const;

    // Methods
    void updateCameraPos(CameraDirection dir);
    [[nodiscard]] static Matrix4 getFinalMatrix();
    void resetCamera();

private:
    explicit Camera(const Vector4& position);

    /**
    * The unique instance of Camera.
    */
    static Camera* _instance;

    /**
    * The camera's position Vector with its x, y and z coordinates.
    */
    Vector4 _cameraPosition;

    /**
    * The vector pointing towards the front of the camera.
    */
    Vector4 _cameraFront;

    /**
    * The vector pointing towards the up direction of the camera.
    */
    Vector4 _cameraUp;

    /**
    * The vector pointing towards the right of the camera.
    */
    Vector4 _cameraRight;

    /**
    * The vector pointing towards the up direction of the world.
    */
    Vector4 _worldUp;

    /**
    * The projection matrix that converts the 3D coordinates into a 2D representation that will be displayed on the
    * screen.
    */
    Matrix4 _projectionMatrix;

    /**
    * The x-axis rotation.
    */
    float _pitch;

    /**
    * The speed at which the different rotations will be done.
    */
    float _speed;

    /**
    * The y-axis rotation.
    */
    float _yaw;

    // Methods
    void _updateCameraVectors();
};

#endif //CAMERA_HPP