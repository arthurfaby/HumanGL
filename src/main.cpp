#include <BufferManager.hpp>
#include <ShaderManager.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"

#define FPS_LIMIT 60

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void render(GLFWwindow* window, const double& now, double& lastRenderTime, unsigned int& frameCount)
{
    // Render here
    glClear(GL_COLOR_BUFFER_BIT);
    BufferManager::drawBuffers();
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
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (window == nullptr)
    {
        Logger::error("main::glfwCreateWindow(): Window creation failed %s. Terminating GLFW.", window);
        glfwTerminate();
        return -1;
    }
    Logger::info("main.cpp::main(): Window created successfully.");

    // Make the window's context current
    glfwMakeContextCurrent(window);
    Logger::info("main.cpp::main(): Window context made current.");

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        Logger::error("main.cpp::main(): GLEW initialization failed. Terminating GLFW.");
        glfwTerminate();
        return -1;
    }

    // Init VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // @formatter:off
    float polygonVertices[] = {
        -0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.33f, 0.33f, 0.0f,
        -0.33f, 0.33f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f
    };


    float colors[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    // @formatter:on

    ShaderManager::init();
    BufferManager::init();
    BufferManager::setColorBuffer(colors, sizeof(colors) / sizeof(float));
    BufferManager::setVertexBuffer(polygonVertices, sizeof(polygonVertices) / sizeof(float));

    glfwSetKeyCallback(window, key_callback);
    Logger::info("main.cpp::main(): Key callback set.");

    // Set the clear color to a grey blue color
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

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
            render(window, now, lastRenderTime, frameCount);
        }
        if (now - lastFpsCountTime > 1.0)
        {
            Logger::info("main.cpp::main(): FPS: %f", frameCount / (now - lastFpsCountTime));
            frameCount = 0;
            lastFpsCountTime = now;
        }
    }
    Logger::info("main.cpp::main(): Window closed. Terminating GLFW.");
    glfwTerminate();
    glfwDestroyWindow(window);
    Logger::info("main.cpp::main(): GLFW terminated.");
    return 0;
}