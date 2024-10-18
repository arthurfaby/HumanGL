#include <Axis.hpp>
#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <cmath>
#include <ShaderManager.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"
#include "MatrixStack.hpp"

#define FPS_LIMIT 144
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700
#define TRANSLATION_SPEED 0.01f
#define ROTATION_SPEED 0.05f

std::vector<Axis*> axises = {};

void handleBodyPartKeys(GLFWwindow* window)
{
    Axis* lastAxis = axises.back();
    float speed = 0;
    if (lastAxis == nullptr)
    {
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        speed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        lastAxis->rotateX(speed);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        speed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        lastAxis->rotateY(speed);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        speed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        lastAxis->rotateZ(speed);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        lastAxis->translate(0.0f, TRANSLATION_SPEED, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        lastAxis->translate(0.0f, -TRANSLATION_SPEED, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        lastAxis->translate(-TRANSLATION_SPEED, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        lastAxis->translate(TRANSLATION_SPEED, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        lastAxis->setPivotPoint(Vector4(0.0f, 0.5f, 0.0f, 1.0f));
    }
}

static void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
    {
        Logger::debug("main.cpp::key_callback(): Adding a new axis.");
        Axis* lastAxis = axises.back();
        Axis* newAxis = new Axis();
        if (lastAxis)
        {
            newAxis->addChild(lastAxis);
        }
        axises.push_back(newAxis);
    }
}

void render(GLFWwindow* window,
            const double& now,
            double& lastRenderTime,
            unsigned int& frameCount)
{
    handleBodyPartKeys(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render here
    Axis* parent = axises.back();
    // for (Axis* axis: axises)
    // {
    // Logger::debug("draw axis : %p", axis);
    // axis->draw();
    // }
    if (parent)
    {
        Logger::debug("main.cpp::render(): Drawing parent.");
        parent->draw();
    }
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

    glfwSetKeyCallback(window, key_callback);

    double lastRenderTime = glfwGetTime();
    double lastFpsCountTime = glfwGetTime();
    unsigned int frameCount = 0;

    // Création des parties du corps
    Axis* head = new Axis();
    head->translate(0.0f, 0.21f, 0.0f);
    head->setPivotPoint(Vector4(0.0f, -0.1f, 0.0f, 1.0f));

    Axis* leftArm = new Axis();
    leftArm->translate(-0.21f, -0.21f, 0.0f);

    Axis* rightArm = new Axis();
    rightArm->translate(0.21f, 0, 0.0f);

    Axis* torso = new Axis();

    torso->addChild(leftArm);
    torso->addChild(rightArm);
    torso->addChild(head);

    axises.push_back(torso);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        const double now = glfwGetTime();

        // Limit the frame rate ti FPS_LIMIT
        if ((now - lastRenderTime) >= 1.0 / FPS_LIMIT)
        {
            render(window, now, lastRenderTime, frameCount);
        }
        if (now - lastFpsCountTime > 1.0)
        {
            // Logger::info("main.cpp::main(): FPS: %d",
            // static_cast<int>(std::round(frameCount / (now - lastFpsCountTime))));
            frameCount = 0;
            lastFpsCountTime = now;
        }
    }
    glfwTerminate();
    glfwDestroyWindow(window);
    return 0;
}