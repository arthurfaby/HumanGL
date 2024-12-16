#include <Animation.hpp>
#include <BodyPart.hpp>
#include <BodyPartDefines.hpp>
#include <BufferManager.hpp>
#include <Camera.hpp>
#include <cmath>
#include <Human.hpp>
#include <Matrix4.hpp>
#include <ShaderManager.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "AnimationManager.hpp"
#include "Logger.hpp"
#include "WindowDefines.hpp"

void handleBodyPartKeys(GLFWwindow* window, Human* selectedHuman)
{
    float speed = 0;

    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->scale(1.01f, 1.0f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->scale(0.99f, 1.0f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->scale(1.0f, 1.01f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->scale(1.0f, 0.99f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->scale(1.0f, 1.0f, 1.01f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->scale(1.0f, 1.0f, 0.99f);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        AnimationManager::select(STAYING_PUT);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        AnimationManager::select(WALKING);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        AnimationManager::select(JUMPING);
    }
    // Rotate the target body part on the positive x-axis
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->rotateX(ROTATION_SPEED);
    }
    // Rotate the target body part on the negative x-axis
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->rotateX(-ROTATION_SPEED);
    }
    // Rotate the target body part on the positive y-axis
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->rotateY(-ROTATION_SPEED);
    }
    // Rotate the target body part on the negative y-axis
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        selectedHuman->getRoot()->rotateY(ROTATION_SPEED);
    }
    // Rotate the target body part on the z-axis
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        speed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        selectedHuman->getLeftLowerArm()->rotateZ(speed);
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
    // Move the camera to the left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Camera::getInstance().updateCameraPos(LEFT);
    }
    // Move the camera to the right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Camera::getInstance().updateCameraPos(RIGHT);
    }
    // Move the camera downward
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        Camera::getInstance().updateCameraPos(DOWN);
    }
    // Move the camera upward
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Camera::getInstance().updateCameraPos(UP);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        Camera::getInstance().resetCamera();
        selectedHuman->resetTranslations();
        selectedHuman->resetMemberRotations();
        selectedHuman->getRoot()->setXRotation(0.0f);
        selectedHuman->getRoot()->setYRotation(0.0f);
        selectedHuman->getRoot()->setZRotation(0.0f);
    }
}

static void key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void render(GLFWwindow* window, Human* selectedHuman)
{
    handleBodyPartKeys(window, selectedHuman);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    selectedHuman->getRoot()->applyTransformation();

    const Matrix4 finalMatrix = Camera::getFinalMatrix();

    const GLint projection = glGetUniformLocation(ShaderManager::getProgramId(), "projection");
    if (projection == -1)
    {
        Logger::error("Uniform 'projection' not found in the shader program.");
    }
    glUniformMatrix4fv(projection, 1, GL_TRUE, finalMatrix.getData());
    AnimationManager::update();
    // Render here
    BufferManager::drawAll();

    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
}

static void handleDebugMode(const int argc, char** argv)
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

    Human* steve = new Human();
    AnimationManager::init(steve);
    BufferManager::init();
    ShaderManager::init();

    glfwSetKeyCallback(window, key_callback);

    double lastRenderTime = glfwGetTime();
    double lastFpsCountTime = glfwGetTime();
    unsigned int frameCount = 0;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        const double now = glfwGetTime();

        // Limit the frame rate to FPS_LIMIT
        if (now - lastRenderTime >= 1.0 / FPS_LIMIT)
        {
            render(window, steve);
            frameCount++;
            lastRenderTime = now;
        }
        if (now - lastFpsCountTime > 1.0)
        {
            frameCount = 0;
            lastFpsCountTime = now;
        }
    }
    glfwTerminate();
    glfwDestroyWindow(window);
    delete steve;
    glDeleteProgram(ShaderManager::getProgramId());
    BufferManager::clean();
    Camera::deleteCamera();
    AnimationManager::clean();
    return 0;
}