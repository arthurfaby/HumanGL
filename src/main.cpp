#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <Camera.hpp>
#include <cmath>
#include <map>
#include <Matrix4.hpp>
#include <ShaderManager.hpp>
#include <Vector4.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"
#include "WindowDefines.hpp"

BodyPart* torso;
BodyPart* rightArm;
BodyPart* leftArm;
BodyPart* rightLowerArm;
BodyPart* leftLowerArm;
BodyPart* head;
BodyPart* rightLeg;
BodyPart* leftLeg;
BodyPart* rightLowerLeg;
BodyPart* leftLowerLeg;

BodyPart* targetBodyPart;
BodyPart* root;

std::map<std::array<int, 3>, BodyPart*> bodypartMap;

GLuint pickingFramebuffer, pickingTexture;

void handleBodyPartKeys(GLFWwindow* window)
{
    if (targetBodyPart == nullptr)
    {
        return;
    }

    // Rotate the target body part on the positive x-axis
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        targetBodyPart->rotateX(ROTATION_SPEED);
    }
    // Rotate the target body part on the negative x-axis
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        targetBodyPart->rotateX(-ROTATION_SPEED);
    }
    // Rotate the target body part on the positive y-axis
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        targetBodyPart->rotateY(-ROTATION_SPEED);
    }
    // Rotate the target body part on the negative y-axis
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        targetBodyPart->rotateY(ROTATION_SPEED);
    }
    // Rotate the target body part on the z-axis
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        float speed = 0;
        speed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        targetBodyPart->rotateZ(speed);
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
}

static void mouse_button_callback(GLFWwindow* window, const int button, const int action, const int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        double mouseX, mouseY;
        unsigned char pixel[3];

        // Get the window based coordinates of the mouse in which (0,0) is the top left corner
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Convert the window based coordinates to OpenGL based coordinates in which (0,0) is the bottom left corner
        mouseY = WINDOW_HEIGHT - mouseY;
        glReadPixels(static_cast<int>(mouseX), static_cast<int>(mouseY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);

        if (bodypartMap.contains({pixel[0], pixel[1], pixel[2]}))
        {
            BodyPart* newTarget = bodypartMap.find({pixel[0], pixel[1], pixel[2]})->second;
            // Reset the color of the previously targeted body part
            targetBodyPart->resetColor();

            // Update the targeted body part
            targetBodyPart = newTarget;

            // Set the color of the new targeted body part
            newTarget->setColor(TARGET_COLOR);
        }
        else // If the user clicked on the background
        {
            targetBodyPart->resetColor();
            targetBodyPart = torso;
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

static void render(GLFWwindow* window)
{
    handleBodyPartKeys(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    root->applyTransformation();

    const Matrix4 finalMatrix = Camera::getFinalMatrix();

    const GLint projection = glGetUniformLocation(ShaderManager::getProgramId(), "projection");
    if (projection == -1)
    {
        Logger::error("Uniform 'projection' not found in the shader program.");
    }
    glUniformMatrix4fv(projection, 1, GL_TRUE, finalMatrix.getData());
    glUniform1i(glGetUniformLocation(ShaderManager::getProgramId(), "isPicked"), GL_FALSE);

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
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    double lastRenderTime = glfwGetTime();
    double lastFpsCountTime = glfwGetTime();
    unsigned int frameCount = 0;

    // TODO libérer mémoire
    torso = new BodyPart();
    torso->setWidth(0.1);
    torso->setHeight(0.1);
    torso->setDepth(0.1);
    torso->setDefaultColor(TORSO_COLOR);

    bodypartMap[{TORSO_COLOR}] = torso;

    rightArm = new BodyPart();
    rightArm->setWidth(0.3f);
    rightArm->setHeight(0.05f);
    rightArm->setDepth(0.05f);
    rightArm->setDefaultColor(RIGHT_ARM_COLOR);

    bodypartMap[{RIGHT_ARM_COLOR}] = rightArm;

    leftArm = new BodyPart();
    leftArm->setHeight(0.05f);
    leftArm->setDepth(0.05f);
    leftArm->setPivotPoint(Vector4(-0.10f, 0, 0, 1));
    leftArm->translate(0.2f, 0.15f, 0.0f);
    leftArm->setDefaultColor(LEFT_ARM_COLOR);

    bodypartMap[{LEFT_ARM_COLOR}] = leftArm;

    rightLowerArm = new BodyPart();
    rightLowerArm->setHeight(rightArm->getHeight() / 2);
    rightLowerArm->setDepth(rightArm->getDepth() / 2);
    rightLowerArm->setPivotPoint(Vector4(0.10f, 0, 0, 1));
    rightLowerArm->translate(-0.2f, 0, 0);
    rightLowerArm->setDefaultColor(RIGHT_LOWER_ARM_COLOR);

    bodypartMap[{RIGHT_LOWER_ARM_COLOR}] = rightLowerArm;

    leftLowerArm = new BodyPart();
    leftLowerArm->setHeight(leftArm->getHeight() / 2);
    leftLowerArm->setDepth(leftArm->getDepth() / 2);
    leftLowerArm->setPivotPoint(Vector4(-0.10f, 0, 0, 1));
    leftLowerArm->translate(0.2f, 0, 0);
    leftLowerArm->setDefaultColor(LEFT_LOWER_ARM_COLOR);

    bodypartMap[{LEFT_LOWER_ARM_COLOR}] = leftLowerArm;

    head = new BodyPart();
    head->setHeight(0.1f);
    head->setWidth(0.1f);
    head->setDepth(0.1f);
    head->setPivotPoint(Vector4(0, -0.05f, 0, 1));
    head->translate(0.0f, 0.25f, 0.0f);
    head->setDefaultColor(HEAD_COLOR);

    bodypartMap[{HEAD_COLOR}] = head;

    leftLeg = new BodyPart();
    leftLeg->setHeight(0.2f);
    leftLeg->setWidth(0.05f);
    leftLeg->setDepth(0.05f);
    leftLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    leftLeg->translate(0.05f, -0.3f, 0.0f);
    leftLeg->setDefaultColor(LEFT_LEG_COLOR);

    bodypartMap[{LEFT_LEG_COLOR}] = leftLeg;

    leftLowerLeg = new BodyPart();
    leftLowerLeg->setHeight(0.2f);
    leftLowerLeg->setWidth(0.05f / 2.0f);
    leftLowerLeg->setDepth(0.05f / 2.0f);
    leftLowerLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    leftLowerLeg->translate(0.0f, -0.2f, 0.0f);
    leftLowerLeg->setDefaultColor(LEFT_LOWER_LEG_COLOR);

    bodypartMap[{LEFT_LOWER_LEG_COLOR}] = leftLowerLeg;

    rightLeg = new BodyPart();
    rightLeg->setHeight(0.2f);
    rightLeg->setWidth(0.05f);
    rightLeg->setDepth(0.05f);
    rightLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    rightLeg->translate(-0.05f, -0.3f, 0.0f);
    rightLeg->setDefaultColor(RIGHT_LEG_COLOR);

    bodypartMap[{RIGHT_LEG_COLOR}] = rightLeg;

    rightLowerLeg = new BodyPart();
    rightLowerLeg->setHeight(0.2f);
    rightLowerLeg->setWidth(0.05f / 2.0f);
    rightLowerLeg->setDepth(0.05f / 2.0f);
    rightLowerLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    rightLowerLeg->translate(0.0f, -0.2f, 0.0f);
    rightLowerLeg->setDefaultColor(RIGHT_LOWER_LEG_COLOR);

    bodypartMap[{RIGHT_LOWER_LEG_COLOR}] = rightLowerLeg;

    torso->addChild(head);
    torso->addChild(leftLeg);
    leftLeg->addChild(leftLowerLeg);
    torso->addChild(rightLeg);
    rightLeg->addChild(rightLowerLeg);
    torso->addChild(rightArm);
    rightArm->addChild(rightLowerArm);
    torso->addChild(leftArm);
    leftArm->addChild(leftLowerArm);

    root = torso;
    targetBodyPart = torso;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        const double now = glfwGetTime();

        // Limit the frame rate to FPS_LIMIT
        if (now - lastRenderTime >= 1.0 / FPS_LIMIT)
        {
            render(window);
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
    return 0;
}