#include <AnimationManager.hpp>
#include <BodyPart.hpp>
#include <BodyPartDefines.hpp>
#include <BufferManager.hpp>
#include <Camera.hpp>
#include <Human.hpp>
#include <keybindings.hpp>
#include <Logger.hpp>
#include <ShaderManager.hpp>
#include <WindowDefines.hpp>
#include <GLFW/glfw3.h>

static void mouse_button_callback(GLFWwindow* window, const int button, const int action, const int mods)
{
    auto* selectedHuman = static_cast<Human*>(glfwGetWindowUserPointer(window));

    if (selectedHuman == nullptr)
    {
        Logger::error("main.cpp::mouse_button_callback(): Steve is null.");
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        double mouseX, mouseY;
        unsigned char pixel[3];

        // Get the window based coordinates of the mouse in which (0,0) is the top left corner
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Convert the window based coordinates to OpenGL based coordinates in which (0,0) is the bottom left corner
        mouseY = WINDOW_HEIGHT - mouseY;
        glReadPixels(static_cast<int>(mouseX), static_cast<int>(mouseY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);

        if (Human::getColorToBodyPartMap().contains({pixel[0], pixel[1], pixel[2]}))
        {
            BodyPart* newTarget = Human::getColorToBodyPartMap().find({pixel[0], pixel[1], pixel[2]})->second;
            // Reset the color of the previously targeted body part
            selectedHuman->getTarget()->resetColor();

            // Update the targeted body part
            selectedHuman->setTarget(newTarget);

            // Set the color of the new targeted body part
            newTarget->setColor(TARGET_COLOR);
        }
        else // If the user clicked on the background
        {
            selectedHuman->getTarget()->resetColor();
            selectedHuman->setTarget(selectedHuman->getTorso());
        }
    }
}

static void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void render(GLFWwindow* window, const Human* selectedHuman)
{
    handleKeys(window, selectedHuman);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (selectedHuman)
    {
        selectedHuman->getRoot()->applyTransformation();
    }

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
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "El famoso Stevo", nullptr, nullptr);
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

    auto* steve = new Human();
    AnimationManager::init(steve);
    BufferManager::init();
    ShaderManager::init();

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowUserPointer(window, steve);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

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