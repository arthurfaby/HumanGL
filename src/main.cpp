#include <BodyPart.hpp>
#include <BufferManager.hpp>
#include <Camera.hpp>
#include <cmath>
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

void handleBodyPartKeys(GLFWwindow* window)
{
    float speed = 0;
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
        speed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
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

static void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void render(GLFWwindow* window)
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

    ShaderManager::init();
    BufferManager::init();

    glfwSetKeyCallback(window, key_callback);

    double lastRenderTime = glfwGetTime();
    double lastFpsCountTime = glfwGetTime();
    unsigned int frameCount = 0;

    // Human* Steve = new Human();

    // Création des parties du corps
    // TODO libérer mémoire
    torso = new BodyPart();
    torso->setHeight(0.4f);
    torso->setWidth(0.2f);
    torso->setDepth(0.1f);
    torso->setColor(TORSO_COLOR);

    rightArm = new BodyPart();
    rightArm->setHeight(0.05f);
    rightArm->setDepth(0.05f);
    rightArm->translate(-0.2f, 0.15f, 0.0f);
    rightArm->setPivotPoint(Vector4(0.08f, 0, 0, 1));
    rightArm->setColor(RIGHT_ARM_COLOR);

    leftArm = new BodyPart();
    leftArm->setHeight(0.05f);
    leftArm->setDepth(0.05f);
    leftArm->setPivotPoint(Vector4(-0.10f, 0, 0, 1));
    leftArm->translate(0.2f, 0.15f, 0.0f);
    leftArm->setColor(LEFT_ARM_COLOR);

    rightLowerArm = new BodyPart();
    rightLowerArm->setHeight(rightArm->getHeight() / 2);
    rightLowerArm->setDepth(rightArm->getDepth() / 2);
    rightLowerArm->setPivotPoint(Vector4(0.10f, 0, 0, 1));
    rightLowerArm->translate(-0.2f, 0, 0);
    rightLowerArm->setColor(RIGHT_LOWER_ARM_COLOR);

    leftLowerArm = new BodyPart();
    leftLowerArm->setHeight(leftArm->getHeight() / 2);
    leftLowerArm->setDepth(leftArm->getDepth() / 2);
    leftLowerArm->setPivotPoint(Vector4(-0.10f, 0, 0, 1));
    leftLowerArm->translate(0.2f, 0, 0);
    leftLowerArm->setColor(LEFT_LOWER_ARM_COLOR);

    head = new BodyPart();
    head->setHeight(0.1f);
    head->setWidth(0.1f);
    head->setDepth(0.1f);
    head->setPivotPoint(Vector4(0, -0.05f, 0, 1));
    head->translate(0.0f, 0.25f, 0.0f);
    head->setColor(HEAD_COLOR);

    leftLeg = new BodyPart();
    leftLeg->setHeight(0.2f);
    leftLeg->setWidth(0.05f);
    leftLeg->setDepth(0.05f);
    leftLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    leftLeg->translate(0.05f, -0.3f, 0.0f);
    leftLeg->setColor(LEFT_LEG_COLOR);

    leftLowerLeg = new BodyPart();
    leftLowerLeg->setHeight(0.2f);
    leftLowerLeg->setWidth(0.05f / 2.0f);
    leftLowerLeg->setDepth(0.05f / 2.0f);
    leftLowerLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    leftLowerLeg->translate(0.0f, -0.2f, 0.0f);
    leftLowerLeg->setColor(LEFT_LOWER_LEG_COLOR);

    rightLeg = new BodyPart();
    rightLeg->setHeight(0.2f);
    rightLeg->setWidth(0.05f);
    rightLeg->setDepth(0.05f);
    rightLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    rightLeg->translate(-0.05f, -0.3f, 0.0f);
    rightLeg->setColor(RIGHT_LEG_COLOR);

    rightLowerLeg = new BodyPart();
    rightLowerLeg->setHeight(0.2f);
    rightLowerLeg->setWidth(0.05f / 2.0f);
    rightLowerLeg->setDepth(0.05f / 2.0f);
    rightLowerLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    rightLowerLeg->translate(0.0f, -0.2f, 0.0f);
    rightLowerLeg->setColor(RIGHT_LOWER_LEG_COLOR);

    torso->addChild(head);
    torso->addChild(leftLeg);
    leftLeg->addChild(leftLowerLeg);
    torso->addChild(rightLeg);
    rightLeg->addChild(rightLowerLeg);
    torso->addChild(rightArm);
    torso->addChild(leftArm);
    rightArm->addChild(rightLowerArm);
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