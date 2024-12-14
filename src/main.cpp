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
#include "Logger.hpp"
#include "WindowDefines.hpp"
Animation stayingPutAnimation;
Animation walkingAnimation;
Animation jumpingAnimation;
Animation* selectedAnimation = &stayingPutAnimation;

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
        selectedAnimation = &stayingPutAnimation;
        stayingPutAnimation.resetAnimation();
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        selectedAnimation = &walkingAnimation;
        walkingAnimation.resetAnimation();
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        selectedAnimation = &jumpingAnimation;
        jumpingAnimation.resetAnimation();
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
    selectedAnimation->update();
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

void generateStayingPutKeyframes(Human* human)
{
    stayingPutAnimation.addKeyframe(0.0f,
                                    [human](const double factor)
                                    {
                                        auto angle = 0.0f + factor * M_PI / 64;
                                        human->resetTranslations();
                                        human->resetMemberRotations();
                                        human->getRightArm()->setXRotation(angle)
                                                .setZRotation(M_PI / 2 - M_PI / 50);
                                        human->getLeftArm()->setXRotation(-angle)
                                                .setZRotation(-M_PI / 2 + M_PI / 50);
                                    });

    stayingPutAnimation.addKeyframe(1.0f,
                                    [human](const double factor)
                                    {
                                        auto angle = M_PI / 64 - 2 * factor * M_PI / 64;
                                        human->getRightArm()->setXRotation(angle);
                                        human->getLeftArm()->setXRotation(-angle);
                                    });;
    stayingPutAnimation.addKeyframe(3.0f,
                                    [human](const double factor)
                                    {
                                        auto angle = -M_PI / 64 + factor * M_PI / 64;
                                        human->getRightArm()->setXRotation(angle);
                                        human->getLeftArm()->setXRotation(-angle);
                                    });
    stayingPutAnimation.addKeyframe(4.0f,
                                    [human](const double factor)
                                    {
                                    });;
}

void generateJumpingKeyframes(Human* human)
{
    jumpingAnimation.addKeyframe(0.0f,
                                 [human](const float factor)
                                 {
                                     human->resetMemberRotations();
                                     human->resetTranslations();
                                     human->getRightLeg()->setXRotation(factor * M_PI / 4);
                                     human->getLeftLeg()->setXRotation(factor * M_PI / 4);

                                     human->getRightLowerLeg()->setXRotation(factor * -M_PI / 2);
                                     human->getLeftLowerLeg()->setXRotation(factor * -M_PI / 2);

                                     human->getRightArm()->setYRotation(-M_PI / 2).setZRotation(
                                         3 * M_PI / 8);
                                     human->getRightLowerArm()->setZRotation(-3 * M_PI / 8);

                                     human->getLeftArm()->setYRotation(M_PI / 2).setZRotation(
                                         -3 * M_PI / 8);
                                     human->getLeftLowerArm()->setZRotation(3 * M_PI / 8);

                                     human->getRoot()->setTranslateY(factor * -0.17f);
                                 });
    jumpingAnimation.addKeyframe(0.5f,
                                 [human](const float factor)
                                 {
                                     human->getRightLeg()->setXRotation(M_PI / 4 - factor * M_PI / 4);
                                     human->getLeftLeg()->setXRotation(M_PI / 4 - factor * M_PI / 4);

                                     human->getRightLowerLeg()->setXRotation(-M_PI / 2 + factor * M_PI / 2);
                                     human->getLeftLowerLeg()->setXRotation(-M_PI / 2 + factor * M_PI / 2);

                                     human->getRightArm()->setZRotation(
                                         3 * M_PI / 8 - factor * 6 * M_PI / 8);
                                     human->getRightLowerArm()->setZRotation(-3 * M_PI / 8 + factor * 3 * M_PI / 8);

                                     human->getLeftArm()->setZRotation(
                                         -3 * M_PI / 8 + factor * 6 * M_PI / 8);
                                     human->getLeftLowerArm()->setZRotation(3 * M_PI / 8 - factor * 3 * M_PI / 8);

                                     human->getRoot()->setTranslateY(-0.17 + factor * 0.3);
                                 });
    jumpingAnimation.addKeyframe(0.75f,
                                 [human](const float factor)
                                 {
                                     human->getRoot()->setTranslateY(0.13f + factor * 0.3f);
                                 });
    jumpingAnimation.addKeyframe(1.0f,
                                 [human](const float factor)
                                 {
                                     human->getRoot()->setTranslateY(0.43f - factor * 0.43f);

                                     human->getRightArm()->setZRotation(
                                         -3 * M_PI / 8 + factor * 6 * M_PI / 8);
                                     human->getRightLowerArm()->setZRotation(factor * -3 * M_PI / 8);

                                     human->getLeftArm()->setZRotation(
                                         3 * M_PI / 8 - factor * 6 * M_PI / 8);
                                     human->getLeftLowerArm()->setZRotation(factor * 3 * M_PI / 8);
                                 });
    jumpingAnimation.addKeyframe(1.5f,
                                 [human](const double factor)
                                 {
                                 });
}

void generateWalkingKeyframes(Human* human)
{
    walkingAnimation.addKeyframe(0.0f,
                                 [human](const double factor)
                                 {
                                     const auto angle = static_cast<float>(factor * M_PI / 8);
                                     human->resetMemberRotations();
                                     human->resetTranslations();
                                     human->getRightLeg()->setXRotation(angle);
                                     human->getLeftLeg()->setXRotation(-angle);

                                     human->getRightLowerLeg()->setXRotation(-angle / 2);
                                     human->getLeftLowerLeg()->setXRotation(angle / 2);

                                     human->getRightArm()->setZRotation(M_PI / 2 - M_PI / 50)
                                             .setXRotation(-angle);
                                     human->getLeftArm()->setZRotation(-M_PI / 2 + M_PI / 50)
                                             .setXRotation(angle);

                                     human->getRightLowerArm()->setXRotation(-angle);
                                     human->getLeftLowerArm()->setXRotation(angle);

                                     human->getHead()->setYRotation(factor * M_PI / 16);
                                 });

    walkingAnimation.addKeyframe(0.5f,
                                 [human](const double factor)
                                 {
                                     const auto angle = static_cast<float>(M_PI / 8 - 2 * factor * M_PI / 8);
                                     human->getRightLeg()->setXRotation(angle);
                                     human->getLeftLeg()->setXRotation(-angle);

                                     human->getRightLowerLeg()->setXRotation(-angle / 2);
                                     human->getLeftLowerLeg()->setXRotation(angle / 2);

                                     human->getRightArm()->setXRotation(-angle);
                                     human->getLeftArm()->setXRotation(angle);

                                     human->getRightLowerArm()->setXRotation(-angle);
                                     human->getLeftLowerArm()->setXRotation(angle);

                                     human->getHead()->setYRotation(M_PI / 16 - 2 * factor * M_PI / 16);
                                 });

    walkingAnimation.addKeyframe(1.5f,
                                 [human](const double factor)
                                 {
                                     const auto angle = static_cast<float>(-M_PI / 8 + factor * M_PI / 8);
                                     human->getRightLeg()->setXRotation(angle);
                                     human->getLeftLeg()->setXRotation(-angle);

                                     human->getRightLowerLeg()->setXRotation(-angle / 2);
                                     human->getLeftLowerLeg()->setXRotation(angle / 2);

                                     human->getRightArm()->setXRotation(-angle);
                                     human->getLeftArm()->setXRotation(angle);

                                     human->getRightLowerArm()->setXRotation(-angle);
                                     human->getLeftLowerArm()->setXRotation(angle);

                                     human->getHead()->setYRotation(-M_PI / 16 + factor * M_PI / 16);
                                 });

    walkingAnimation.addKeyframe(2.0f,
                                 [human](const double factor)
                                 {
                                     human->getRightLeg()->setXRotation(0.0f);
                                     human->getLeftLeg()->setXRotation(0.0f);

                                     human->getRightLowerLeg()->setXRotation(0.0f);
                                     human->getLeftLowerLeg()->setXRotation(0.0f);

                                     human->getRightArm()->setXRotation(0.0f);
                                     human->getLeftArm()->setXRotation(0.0f);

                                     human->getRightLowerArm()->setXRotation(0.0f);
                                     human->getLeftLowerArm()->setXRotation(0.0f);
                                 });
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

    Human* steve = new Human();

    generateWalkingKeyframes(steve);
    generateJumpingKeyframes(steve);
    generateStayingPutKeyframes(steve);
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
    // Camera::deleteCamera();
    return 0;
}