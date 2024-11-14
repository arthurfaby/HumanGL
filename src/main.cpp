#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <Camera.hpp>
#include <cmath>
#include <Matrix4.hpp>
#include <cmath>
#include <ShaderManager.hpp>
#include <Vector4.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"
#include "WindowDefines.hpp"

static void key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void render(GLFWwindow* window,
            BodyPart& selectedBodyPart,
            const double& now,
            double& lastRenderTime,
            unsigned int& frameCount)
{
    handleBodyPartKeys(window, selectedBodyPart);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Matrix4 translationMatrix = Matrix4::createTranslationMatrix(
                                               Camera::getInstance().getPosition().getX(),
                                               Camera::getInstance().getPosition().getY(),
                                               Camera::getInstance().getPosition().getZ());

    const Matrix4 rotationMatrix = Matrix4::createRotationYMatrix(-Camera::getInstance().getYRotation()) *
                                        Matrix4::createRotationXMatrix(-Camera::getInstance().getXRotation());

    const Matrix4 finalMatrix = Camera::getInstance().getProjectionMatrix() * translationMatrix * rotationMatrix;

    const GLint projection = glGetUniformLocation(ShaderManager::getProgramId(), "projection");
    if (projection == -1)
    {
        Logger::error("Uniform 'projection' not found in the shader program.");
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

static void handleDebugMode(const int argc, char **argv)
{
    for (int i = 0; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--debug")
        {
            Logger::setDebug(true);
        }
    }
}

int main(const int argc, char** argv)
{
    handleDebugMode(argc, argv);

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
    BodyPart torso2 = BodyPart(Vector4(0.5f, 0.5f, 0.5f));
    Vector4 defaultPosition = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    BodyPart head = BodyPart(defaultPosition, Vector4(0.0f, 0.31f, 0.0f, 0.0f));
    BodyPart torso = BodyPart(defaultPosition, Vector4());
    BodyPart upperLeftArm = BodyPart(defaultPosition, Vector4(0.31f, 0.1f, 0.0f, 0.0f));
    BodyPart lowerLeftArm = BodyPart(defaultPosition, Vector4(0.31f, 0.0f, 0.0f, 0.0f));
    BodyPart upperRightArm = BodyPart(defaultPosition, Vector4(-0.31f, 0.1f, 0.0f, 0.0f));
    BodyPart lowerRightArm = BodyPart(defaultPosition, Vector4(-0.31f, 0.0f, 0.0f, 0.0f));
    BodyPart upperLeftLeg = BodyPart(defaultPosition, Vector4(0.16f, -0.31f, 0.0f, 0.0f));
    BodyPart lowerLeftLeg = BodyPart(defaultPosition, Vector4(0.0f, -0.31f, 0.0f, 0.0f));
    BodyPart upperRightLeg = BodyPart(defaultPosition, Vector4(-0.16f, -0.31f, 0.0f, 0.0f));
    BodyPart lowerRightLeg = BodyPart(defaultPosition, Vector4(0.0f, -0.31f, 0.0f, 0.0f));

    torso.addChild(&head);
    torso.addChild(&upperRightArm);
    torso.addChild(&upperLeftArm);
    torso.addChild(&upperRightLeg);
    torso.addChild(&upperLeftLeg);
    upperRightArm.addChild(&lowerRightArm);
    upperLeftArm.addChild(&lowerLeftArm);
    upperRightLeg.addChild(&lowerRightLeg);
    upperLeftLeg.addChild(&lowerLeftLeg);

    BodyPart& selectedBodyPart = torso;

    glfwSetKeyCallback(window, key_callback);

    double lastRenderTime = glfwGetTime();
    double lastFpsCountTime = glfwGetTime();
    unsigned int frameCount = 0;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        const double now = glfwGetTime();

        // Limit the frame rate ti FPS_LIMIT
        if ((now - lastRenderTime) >= 1.0 / FPS_LIMIT)
        {
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

            // Move the camera forward
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                Camera::getInstance().updateCameraPos(FORWARD);
            }

            // Move the camera backward
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                Camera::getInstance().updateCameraPos(BACKWARD);
            }

            // Move the camera to the right
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                Camera::getInstance().updateCameraPos(RIGHT);
            }

            // Move the camera to the left
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                Camera::getInstance().updateCameraPos(LEFT);
            }

            // Move the camera upward
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                Camera::getInstance().updateCameraPos(UP);
            }

            // Move the camera downward
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                Camera::getInstance().updateCameraPos(DOWN);
            }

            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                Camera::getInstance().setXRotation(UP);
            }

            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                Camera::getInstance().setXRotation(DOWN);
            }

            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            {
                Camera::getInstance().setYRotation(RIGHT);
            }

            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            {
                Camera::getInstance().setYRotation(LEFT);
            }

            render(window, now, lastRenderTime, frameCount);
        // Limit the frame rate ti FPS_LIMIT
        if ((now - lastRenderTime) >= 1.0 / FPS_LIMIT)
        {
            render(window, selectedBodyPart, now, lastRenderTime, frameCount);
        }

        if (now - lastFpsCountTime > 1.0)
        {
            Logger::info("main.cpp::main(): FPS: %d",
                         static_cast<int>(std::round(frameCount / (now - lastFpsCountTime))));
            frameCount = 0;
            lastFpsCountTime = now;
        }
    }
    glfwTerminate();
    glfwDestroyWindow(window);
    return 0;
}