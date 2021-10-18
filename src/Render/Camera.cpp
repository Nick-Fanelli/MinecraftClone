#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

static float s_LastX, s_LastY;
static bool s_FirstMouse = true;

void Camera::MouseCursorCallback(GLFWwindow* window, double xPos, double yPos) {

    if(s_FirstMouse) {
        s_LastX = xPos;
        s_LastY = yPos;
        s_FirstMouse = false;
    }

    float xOffset = xPos - s_LastX;
    float yOffset = s_LastY - yPos;

    s_LastX = xPos;
    s_LastY = yPos;

    static constexpr float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    s_Rotation.x += xOffset;
    s_Rotation.y += yOffset;

    if(s_Rotation.y > 89.0f)
        s_Rotation.y = 89.0f;
    else if(s_Rotation.y < -89.0f)
        s_Rotation.y = -89.0f;

    UpdateViewMatrix();
}

void Camera::CalculateViewProjectionMatrix() {
    s_ViewProjectionMatrix = s_ProjectionMatrix * s_ViewMatrix;
}

void Camera::UpdateProjectionMatrix() {
    s_ProjectionMatrix = glm::perspective(glm::radians(s_FOV), s_AspectRatio, s_ZNear, s_ZFar);
    UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
    glm::vec3 front;
    front.x = cos(glm::radians(s_Rotation.x)) * cos(glm::radians(s_Rotation.y));
    front.y = sin(glm::radians(s_Rotation.y));
    front.z = sin(glm::radians(s_Rotation.x)) * cos(glm::radians(s_Rotation.y));
    s_Front = glm::normalize(front);

    s_ViewMatrix = glm::lookAt(s_Position, s_Position + s_Front, s_Up);

    CalculateViewProjectionMatrix();
}   