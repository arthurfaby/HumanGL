#include <ShaderManager.hpp>
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

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // @formatter:off
    const GLfloat polygonVertices[] = {
        -0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.5f, -0.25f, 0.0f,
        -0.5f, -0.25f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f
    };
    // @formatter:on

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygonVertices), polygonVertices, GL_STATIC_DRAW);
    // This will identify our vertex buffer

    ShaderManager::init();

    glfwSetKeyCallback(window, key_callback);
    Logger::info("main.cpp::main(): Key callback set.");

    // Set the clear color to a grey blue color
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, 0, (void*) 0);

        glDrawArrays(GL_TRIANGLES, 0, 4 * 3);
        glDisableVertexAttribArray(0);

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