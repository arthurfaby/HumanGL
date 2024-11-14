#ifndef CAMERADEFINES_HPP
#define CAMERADEFINES_HPP

#define FOV static_cast<float>(90)                  // Field of view (in degrees)
#define NEAR_PLANE_Z 0.1f                           // Near clipping plane
#define FAR_PLANE_Z 100.0f                          // Far clipping plane
#define Z_RANGE (NEAR_PLANE_Z - FAR_PLANE_Z)        // Range of the z-axis
#define ASPECT_RATIO (WINDOW_WIDTH / WINDOW_HEIGHT) // Aspect ratio of the window

#endif //CAMERADEFINES_HPP