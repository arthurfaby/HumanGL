#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(const int argc, char **argv)
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
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        Logger::error("main::glfwCreateWindow(): Window creation failed %s. Terminating GLFW.", window);
        glfwTerminate();
        return -1;
    }
    Logger::info("main.cpp::main(): Window created successfully.");

    // Make the window's context current
    glfwMakeContextCurrent(window);
    Logger::info("main.cpp::main(): Window context made current.");

    glfwSetKeyCallback(window, key_callback);
    Logger::info("main.cpp::main(): Key callback set.");

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    Logger::info("main.cpp::main(): Window closed. Terminating GLFW.");
    glfwTerminate();
    glfwDestroyWindow(window);
    Logger::info("main.cpp::main(): GLFW terminated.");
    return 0;
}