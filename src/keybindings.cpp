#ifndef KEYBINDINGS_HPP
#define KEYBINDINGS

#include <AnimationManager.hpp>
#include <BodyPartDefines.hpp>
#include <Camera.hpp>
#include <Human.hpp>
#include <keybindings.hpp>
#include <GLFW/glfw3.h>

void handleBodyPartKeys(GLFWwindow* window, const Human* selectedHuman)
{
    if (selectedHuman->getTarget() == nullptr)
    {
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        AnimationManager::select(STAYING_PUT);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        AnimationManager::select(WALKING);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        AnimationManager::select(JUMPING);
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        AnimationManager::select(NO_ANIMATION);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->scale(1.01f, 1.0f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->scale(0.99f, 1.0f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->scale(1.0f, 1.01f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->scale(1.0f, 0.99f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->scale(1.0f, 1.0f, 1.01f);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->scale(1.0f, 1.0f, 0.99f);
    }
    // Rotate the target body part on the positive x-axis
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->rotateX(ROTATION_SPEED);
    }
    // Rotate the target body part on the negative x-axis
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->rotateX(-ROTATION_SPEED);
    }
    // Rotate the target body part on the positive y-axis
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->rotateY(-ROTATION_SPEED);
    }
    // Rotate the target body part on the negative y-axis
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        selectedHuman->getTarget()->rotateY(ROTATION_SPEED);
    }
    // Rotate the target body part on the z-axis
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        float speed = 0;
        speed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ? -ROTATION_SPEED : ROTATION_SPEED;
        selectedHuman->getTarget()->rotateZ(speed);
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
        selectedHuman->resetMembersTranslations();
        selectedHuman->resetMembersRotations();
        selectedHuman->getRoot()->setXRotation(0.0f);
        selectedHuman->getRoot()->setYRotation(0.0f);
        selectedHuman->getRoot()->setZRotation(0.0f);
    }
}
#endif // KEYBINDINGS_HPP