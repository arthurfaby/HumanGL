#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <Matrix4.hpp>
#include <ShaderManager.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"

#define FPS_LIMIT 60
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700

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
        0.5f, 0.5f, 0,
        0.5f, -0.5f, 0,
        -0.5f, -0.5f, 0,
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

    BodyPart head = BodyPart(Vector4(), Vector4(0.0f, 0.31f, 0.0f, 0.0f));
    BodyPart torso = BodyPart(Vector4(), Vector4());
    BodyPart upperLeftArm = BodyPart(Vector4(), Vector4(0.31f, 0.1f, 0.0f, 0.0f));
    BodyPart lowerLeftArm = BodyPart(Vector4(), Vector4(0.31f, 0.0f, 0.0f, 0.0f));
    BodyPart upperRightArm = BodyPart(Vector4(), Vector4(-0.31f, 0.1f, 0.0f, 0.0f));
    BodyPart lowerRightArm = BodyPart(Vector4(), Vector4(-0.31f, 0.0f, 0.0f, 0.0f));
    BodyPart upperLeftLeg = BodyPart(Vector4(), Vector4(0.16f, -0.31f, 0.0f, 0.0f));
    BodyPart lowerLeftLeg = BodyPart(Vector4(), Vector4(0.0f, -0.31f, 0.0f, 0.0f));
    BodyPart upperRightLeg = BodyPart(Vector4(), Vector4(-0.16f, -0.31f, 0.0f, 0.0f));
    BodyPart lowerRightLeg = BodyPart(Vector4(), Vector4(0.0f, -0.31f, 0.0f, 0.0f));

    torso.addChild(&head);
    torso.addChild(&upperRightArm);
    torso.addChild(&upperLeftArm);
    torso.addChild(&upperRightLeg);
    torso.addChild(&upperLeftLeg);
    upperRightArm.addChild(&lowerRightArm);
    upperLeftArm.addChild(&lowerLeftArm);
    upperRightLeg.addChild(&lowerRightLeg);
    upperLeftLeg.addChild(&lowerLeftLeg);
    torso.updateVertices();

    BodyPart* selectedBodyPart = &torso;

    glfwSetKeyCallback(window, key_callback);

    double lastRenderTime = glfwGetTime();
    double lastFpsCountTime = glfwGetTime();
    unsigned int frameCount = 0;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        const double now = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            selectedBodyPart->setPosition(selectedBodyPart->getPosition() + Vector4(0.0001f, 0.0f, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            selectedBodyPart->setPosition(selectedBodyPart->getPosition() - Vector4(0.0001f, 0.0f, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            selectedBodyPart->setPosition(selectedBodyPart->getPosition() + Vector4(0.0f, 0.0001f, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            selectedBodyPart->setPosition(selectedBodyPart->getPosition() - Vector4(0.0f, 0.0001f, 0.0f, 0.0f));
        }
        // Rotate when pressing X
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            Vector4 selectedBodyPartDir = selectedBodyPart->getDir();
            selectedBodyPartDir.setX(selectedBodyPartDir.getX() + 0.001f);
            selectedBodyPart->setDir(selectedBodyPartDir);
        }

        // Rotate when pressing Y
        if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        {
            Vector4 selectedBodyPartDir = selectedBodyPart->getDir();
            selectedBodyPartDir.setY(selectedBodyPartDir.getY() + 0.001f);
            selectedBodyPart->setDir(selectedBodyPartDir);
        }

        // Rotate when pressing Z
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        {
            Vector4 selectedBodyPartDir = selectedBodyPart->getDir();
            selectedBodyPartDir.setZ(selectedBodyPartDir.getZ() + 0.001f);
            selectedBodyPart->setDir(selectedBodyPartDir);
        }

        // Limit the frame rate ti FPS_LIMIT
        if ((now - lastRenderTime) >= 1.0 / FPS_LIMIT)
        {
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