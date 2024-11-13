#ifndef WINDOWDEFINES_HPP
#define WINDOWDEFINES_HPP

#define WINDOW_WIDTH 1024.0f                                // Window width in pixels
#define WINDOW_HEIGHT 768.0f                                // Window height in pixels
#define ASPECT_RATIO (WINDOW_WIDTH / WINDOW_HEIGHT)         // Aspect ratio of the window
#define FPS_LIMIT 60                                        // Frames per second limit
#define PROJECTION_FORMULA (1 / tanf(ToRadian(FOV / 2)))    // Formula to create the frustum

#endif //WINDOWDEFINES_HPP