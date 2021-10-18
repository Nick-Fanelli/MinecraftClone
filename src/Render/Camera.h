#pragma once

#include "pch.h"

#include <glm/gtx/transform.hpp>

#include "Core/Display.h"

class Camera {

public: 

    static inline void SetAspectRatio(float aspectRatio) { s_AspectRatio = aspectRatio; UpdateProjectionMatrix(); }

    static inline const glm::mat4& GetViewProjection() { return s_ViewProjectionMatrix; }
    static inline const glm::mat4& GetProjectionMatrix() { return s_ProjectionMatrix; }
    static inline const glm::mat4& GetViewMatrix() { return s_ViewMatrix; }

    static inline glm::mat4 GetRotatedViewMatrix() {
        glm::vec3 front;
        front.x = cos(glm::radians(s_Rotation.x)) * cos(glm::radians(s_Rotation.y));
        front.y = sin(glm::radians(s_Rotation.y));
        front.z = sin(glm::radians(s_Rotation.x)) * cos(glm::radians(s_Rotation.y));
        s_Front = glm::normalize(front);

        return s_ProjectionMatrix * glm::lookAt({ 0.0f, 0.0f, 0.0f }, s_Front, s_Up);
    }

    static inline void SetPosition(const glm::vec3& position) { s_Position = position; UpdateViewMatrix(); }
    static inline void Move(const glm::vec3& deltaPosition) { s_Position += deltaPosition; UpdateViewMatrix(); }

    static void MouseCursorCallback(GLFWwindow* window, double xPos, double yPos);

    static const glm::vec3& GetFront() { return s_Front;  }
    static const glm::vec3& GetUp() { return s_Up; }

private:
    static void CalculateViewProjectionMatrix();

    static void UpdateProjectionMatrix();
    static void UpdateViewMatrix();

private:
    static inline glm::mat4 s_ProjectionMatrix;
    static inline glm::mat4 s_ViewMatrix;
    static inline glm::mat4 s_ViewProjectionMatrix;

    static inline glm::vec3 s_Position = { 0.0f, 0.0f, 3.0f };
    static inline glm::vec3 s_Rotation = { -90.0f, 0.0f, 0.0f };

    static inline glm::vec3 s_Front = { 0.0f, 0.0f, -1.0f };
    static inline glm::vec3 s_Up = { 0.0f, 1.0f, 0.0f };

    static inline float s_FOV = 70.0f;
    static inline float s_AspectRatio = 1.0f;

    static inline float s_ZNear = 0.1f;
    static inline float s_ZFar = 1000.0f;

    friend class Player;

};