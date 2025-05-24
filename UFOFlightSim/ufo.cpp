
#define GLM_ENABLE_EXPERIMENTAL

#include "UFO.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <filesystem>



#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp> // Make sure this is included for glm::quat operations
#include <glm/gtx/quaternion.hpp> // For glm::slerp

glm::vec3 worldForward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

void UFO::processInput(GLFWwindow* window, float deltaTime) {
    float speed = 30.0f * deltaTime;
    float leanAngleDegrees = 20.0f;
    float leanSpeed = 4.0f;

    
    glm::quat pitchQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // for W/S forward backward leans
    glm::quat rollQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // for A/D sideways leans

  //  glm::quat targetOrientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);


    bool isMoving = false;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        isMoving = true;
        position += speed * worldForward;
        glm::vec3 currentRight = glm::normalize(glm::cross(worldForward, worldUp));
        pitchQuat = glm::angleAxis(glm::radians(-leanAngleDegrees), currentRight);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        isMoving = true;
        position -= speed * worldForward;
        glm::vec3 currentRight = glm::normalize(glm::cross(worldForward, worldUp));
        pitchQuat = glm::angleAxis(glm::radians(leanAngleDegrees), currentRight);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        isMoving = true;
        position -= glm::normalize(glm::cross(worldForward, worldUp)) * speed;
        rollQuat = glm::angleAxis(glm::radians(-leanAngleDegrees), worldForward);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        isMoving = true;
        position += glm::normalize(glm::cross(worldForward, worldUp)) * speed;
        rollQuat = glm::angleAxis(glm::radians(leanAngleDegrees), worldForward);
    }

    //up and down movements
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed;
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += glm::vec3(0.0f, 1.0f, 0.0f) * speed;



    glm::quat targetOrientation = pitchQuat * rollQuat;

    if (!isMoving) {
        targetOrientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // upright
    }

    orientation = glm::slerp(orientation, targetOrientation, deltaTime * leanSpeed);
    front = glm::normalize(orientation * glm::vec3(0.0f, 0.0f, -1.0f));
    up = glm::normalize(orientation * glm::vec3(0.0f, 1.0f, 0.0f));

}

glm::mat4 UFO::getModelMatrixTop() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model *= glm::mat4_cast(orientation);
    return model;
}

glm::mat4 UFO::getModelMatrixBottom() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position + glm::vec3(0.0f, -0.5f, 0.0f));
    model *= glm::mat4_cast(orientation);
    model = glm::scale(model, glm::vec3(3.0f, 0.6f, 3.0f));
    return model;
}