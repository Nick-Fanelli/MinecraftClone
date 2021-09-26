#include "Camera.h"

void Camera::UpdateProjectionMatrix() {
    s_ProjectionMatrix = glm::perspective(glm::radians(s_FOV), s_AspectRatio, s_ZNear, s_ZFar);
    UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
    s_ViewMatrix = glm::lookAt(s_Position, s_Position + s_Forward, s_Up);
}