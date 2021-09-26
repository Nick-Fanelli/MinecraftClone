#pragma once

#include "pch.h"

#include <glm/gtx/transform.hpp>

class Camera {

public:

    Camera() = delete;
    Camera(const Camera&) = delete;

    static void SetAspectRatio(float aspectRatio) { s_AspectRatio = aspectRatio; UpdateProjectionMatrix(); }

    static void SetPosition(const glm::vec3& position) {
        s_Position = position;
        UpdateViewMatrix();
    }

    static inline glm::mat4 GetViewProjection() {
        return s_ProjectionMatrix * s_ViewMatrix;
    }

protected:
    static void UpdateProjectionMatrix();
    static void UpdateViewMatrix();

private:
    static inline glm::mat4 s_ProjectionMatrix;
    static inline glm::mat4 s_ViewMatrix;

    static inline glm::vec3 s_Position;

    static constexpr glm::vec3 s_Forward = { 0.0f, 0.0f, -1.0f };
    static constexpr glm::vec3 s_Up = { 0.0f, 1.0f, 0.0f };

    static inline float s_FOV = 70.0f, s_AspectRatio, s_ZNear = 0.01f, s_ZFar = 1000.0f;

};