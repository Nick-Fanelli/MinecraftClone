#include "Player.h"

#include "Core/Display.h"

#include "World/Chunk.h"

// 2.5f default
static float s_PlayerSpeed = 10.92f * 2.0f;

void Player::Update(float deltaTime) {
    static GLFWwindow* windowPtr = Display::GetWindowPtr();

    float cameraSpeed = s_PlayerSpeed * deltaTime;
    bool shouldUpdate = false;

    if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS) {
        s_Position += cameraSpeed * glm::vec3{ Camera::GetFront().x, 0.0f, Camera::GetFront().z };
        shouldUpdate = true;
    }

    if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS) {
        s_Position -= cameraSpeed * glm::vec3{ Camera::GetFront().x, 0.0f, Camera::GetFront().z };
        shouldUpdate = true;
    }

    if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS) {
        s_Position -= glm::normalize(glm::cross(Camera::GetFront(), Camera::GetUp())) * cameraSpeed;
        shouldUpdate = true;
    }

    if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS) {
        s_Position += glm::normalize(glm::cross(Camera::GetFront(), Camera::GetUp())) * cameraSpeed;
        shouldUpdate = true;
    }

    if (glfwGetKey(windowPtr, GLFW_KEY_SPACE) == GLFW_PRESS) {
        s_Position += cameraSpeed * Camera::GetUp();
        shouldUpdate = true;
    }

    if (glfwGetKey(windowPtr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        s_Position -= cameraSpeed * Camera::GetUp();
        shouldUpdate = true;
    }

    if (shouldUpdate) {
        Camera::s_Position = s_Position;
        Camera::UpdateViewMatrix();

        glm::vec2 currentChunk = { floor(s_Position.x / Chunk::CHUNK_SIZE), floor(s_Position.z / Chunk::CHUNK_SIZE) };

        if(!s_ChunkManagerPtr->IsChunkCreated(currentChunk.x, currentChunk.y)) {
            glm::vec2 chunks[] = { currentChunk };

            s_ChunkManagerPtr->SetChunks(chunks, 1);
            // s_ChunkManagerPtr->CreateChunk(currentChunk.x, currentChunk.y);
        }

        // std::cout << currentChunk << std::endl;
    }
}