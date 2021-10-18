#pragma once

#include "pch.h"

#include "Render/Camera.h"

class Player {

public:
    static void Update(float deltaTime);

    static void SetPosition(const glm::vec3& position) { s_Position = position; Camera::UpdateViewMatrix(); }
        
    static const glm::vec3& GetPosition() { return s_Position; }

private:
    static inline glm::vec3 s_Position = { 0.0f, 0.0f, 0.0f };

};