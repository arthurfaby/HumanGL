#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <cmath>
#include <Matrix4.hpp>
#include <ShaderManager.hpp>
#include <Vector4.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"

#define ToRadian(x) ((x) * (M_PI / 180.0))

#define WINDOW_WIDTH 1024.0f                        // Window width in pixels
#define WINDOW_HEIGHT 576.0f                        // Window height in pixels
#define ASPECT_RATIO (WINDOW_WIDTH / WINDOW_HEIGHT) // Aspect ratio of the window
#define FPS_LIMIT 60                                // Frames per second limit
#define NEAR_PLANE_Z 0.1f                           // Near clipping plane
#define FAR_PLANE_Z 100.0f                          // Far clipping plane
#define Z_RANGE (NEAR_PLANE_Z - FAR_PLANE_Z)        // Range of the z-axis

Vector4 cameraPos(0.0f, 0.0f, 0.0f, 1.0f);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void render(GLFWwindow* window, const double& now, double& lastRenderTime, unsigned int& frameCount)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    constexpr float fov = 90.0f;
    constexpr float halfFov = fov / 2;
    constexpr float radHalfFov = ToRadian(halfFov);
    const float tanRadHalfFov = tanf(radHalfFov);
    const float inverseTanRadHalfFov = 1 / tanRadHalfFov;

    // @formatter:off
    const Matrix4 matrixProjection({
        inverseTanRadHalfFov / ASPECT_RATIO, 0, 0, 0,
        0, inverseTanRadHalfFov, 0, 0,
        0, 0, (-FAR_PLANE_Z - NEAR_PLANE_Z)/Z_RANGE, (2 * FAR_PLANE_Z * NEAR_PLANE_Z)/Z_RANGE,
        0, 0, 1, 0,
    });
    // @formatter:on

    const Vector4 U(1.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 V(0.0f, 1.0f, 0.0f, 0.0f);
    const Vector4 N(0.0f, 0.0f, 1.0f, 0.0f);

    // @formatter:off
    const Matrix4 uvnMatrix({
        U.getX(), U.getY(), U.getZ(), 0,
        V.getX(), V.getY(), V.getZ(), 0,
        N.getX(), N.getY(), N.getZ(), 0,
        0, 0, 0, 1
    });
    // @formatter:on

    // @formatter:off
    const Matrix4 cameraMatrix = uvnMatrix * Matrix4::createTranslationMatrix(-cameraPos.getX(), -cameraPos.getY(), -cameraPos.getZ());

    const auto finalMatrix = matrixProjection * cameraMatrix * Matrix4::createTranslationMatrix(0, 0, NEAR_PLANE_Z * 5);

    const GLint projection = glGetUniformLocation(ShaderManager::getProgramId(), "projection");
    if (projection == -1)
    {
        Logger::error("Uniform 'projection' not found in the shader program.");
    }
    else
    {
        Logger::debug("Uniform 'projection' initialized");
    }
    glUniformMatrix4fv(projection, 1, GL_TRUE, finalMatrix.getData());

    // Render here
    BufferManager::drawAll();

    glfwSwapBuffers(window);
    frameCount++;
    lastRenderTime = now;

    // Poll for and process events
    glfwPollEvents();
}

int main(const int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--debug")
        {
            Logger::setDebug(true);
        }
    }

    // Initialize the library
    if (!glfwInit())
    {
        Logger::error("main,cpp::main(): GLFW initialization failed. Terminating program.");
        return -1;
    }

    // Disable window resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", nullptr, nullptr);
    if (window == nullptr)
    {
        Logger::error("main::glfwCreateWindow(): Window creation failed %s. Terminating GLFW.", window);
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    // Hide the cursor within the window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        Logger::error("main.cpp::main(): GLEW initialization failed. Terminating GLFW.");
        glfwTerminate();
        return -1;
    }

    // Set the clear color to a grey blue color
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    ShaderManager::init();
    BufferManager::init();

    BodyPart torso = BodyPart(Vector4(0.0f, 0.0f, 0.0f));
    // BodyPart torso2 = BodyPart(Vector4(0.4f, 0.0f, 50.0f));

    glfwSetKeyCallback(window, key_callback);

    double lastRenderTime = glfwGetTime();
    double lastFpsCountTime = glfwGetTime();
    unsigned int frameCount = 0;
    double angle1 = 0;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        const double now = glfwGetTime();

        // Limit the frame rate ti FPS_LIMIT
        if ((now - lastRenderTime) >= 1.0 / FPS_LIMIT)
        {
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            // torso.setPosition(torso.getPosition() + Vector4(0.00001f, 0.0f, 0.0f, 0.0f));
            cameraPos.setX(cameraPos.getX() + 0.01f);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            // torso.setPosition(torso.getPosition() - Vector4(0.00001f, 0.0f, 0.0f, 0.0f));
            cameraPos.setX(cameraPos.getX() - 0.01f);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            // torso.setPosition(torso.getPosition() + Vector4(0.0f, 0.00001f, 0.0f, 0.0f));
            cameraPos.setY(cameraPos.getY() + 0.01f);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            // torso.setPosition(torso.getPosition() - Vector4(0.0f, 0.00001f, 0.0f, 0.0f));
            cameraPos.setY(cameraPos.getY() - 0.01f);
        }

        // Rotate when pressing X
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            Vector4 torsoDir = torso.getDir();
            torsoDir.setX(torsoDir.getX() + 0.01f);
            torso.setDir(torsoDir);
        }

        // Rotate when pressing Y
        if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        {
            Vector4 torsoDir = torso.getDir();
            torsoDir.setY(torsoDir.getY() + 0.01f);
            torso.setDir(torsoDir);
        }

        // Rotate when pressing Z
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        {
            Vector4 torsoDir = torso.getDir();
            torsoDir.setZ(torsoDir.getZ() + 0.01f);
            torso.setDir(torsoDir);
        }

        // Increase z-axis when pressing UP_ARROW
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            // Vector4 torsoPos = torso.getPosition();
            // torsoPos.setZ(torsoPos.getZ() + 0.0001f);
            // torso.setPosition(torsoPos);
            cameraPos.setZ(cameraPos.getZ() + 0.01f);
        }

        // Decrease z-axis when pressing DOWN_ARROW
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            // Vector4 torsoPos = torso.getPosition();
            // torsoPos.setZ(torsoPos.getZ() - 0.0001f);
            // torso.setPosition(torsoPos);
            cameraPos.setZ(cameraPos.getZ() - 0.01f);
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            cameraPos = Matrix4::createRotationYMatrix(-10 * std::numbers::pi / 180) * cameraPos;
        }

            render(window, now, lastRenderTime, frameCount);
        }
        if (now - lastFpsCountTime > 1.0)
        {
            Logger::info("main.cpp::main(): FPS: %f", frameCount / (now - lastFpsCountTime));
            frameCount = 0;
            lastFpsCountTime = now;
        }
    }
    glfwTerminate();
    glfwDestroyWindow(window);
    return 0;
}