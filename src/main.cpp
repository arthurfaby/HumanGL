#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <cmath>
#include <ShaderManager.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"

#define FPS_LIMIT 144
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700
#define TRANSLATION_SPEED 0.01f
#define ROTATION_SPEED 0.01f

void handleBodyPartKeys(GLFWwindow* window, BodyPart& selectedBodyPart)
{
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        selectedBodyPart.setPosition(selectedBodyPart.getPosition() + Vector4(TRANSLATION_SPEED, 0.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        selectedBodyPart.setPosition(selectedBodyPart.getPosition() - Vector4(TRANSLATION_SPEED, 0.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        selectedBodyPart.setPosition(selectedBodyPart.getPosition() + Vector4(0.0f, TRANSLATION_SPEED, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        selectedBodyPart.setPosition(selectedBodyPart.getPosition() - Vector4(0.0f, TRANSLATION_SPEED, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        double newAngleX = selectedBodyPart.getAngleX();
        newAngleX += glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        selectedBodyPart.setAngleX(newAngleX);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        double newAngleY = selectedBodyPart.getAngleY();
        newAngleY += glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        selectedBodyPart.setAngleY(newAngleY);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        double newAngleZ = selectedBodyPart.getAngleZ();
        newAngleZ += glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        selectedBodyPart.setAngleZ(newAngleZ);
    }
}

static void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
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

    // @formatter:off
    std::vector<float> vertices = {
        0.3f, 0.3f, 0.0f,
        0.3f, -0.3f, 0.0f,
        -0.3f, -0.3f, 0.0f,
    };

    std::vector<float> verticesColors = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    std::vector<float> vertices2 = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };

    std::vector<float> vertices2Colors = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    std::vector<float> lines = {
        -1.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    std::vector<float> linesColors = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    // @formatter:on

    ShaderManager::init();
    BufferManager::init();

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