#include "PlayState.h"

#include "../Render/MeshRenderer.h"
#include "../Render/Camera.h"

static MeshRenderer s_MeshRenderer;
static Mesh s_Mesh;

void PlayState::OnCreate() {

    s_MeshRenderer.Create();
    // Camera::SetPosition({ 0.0f, 0.0f, 2.0f });

    s_Mesh.Create(
        {
            // Front
            { { 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
            { { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
            { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
            { { 0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
        }, 
        {
            // Front
            0, 1, 2, 
            2, 3, 0
        }
    );

}

void PlayState::OnUpdate(float deltaTime) {

    Camera::Update(deltaTime);

    // Camera::Move({ deltaTime, deltaTime, 2.0f * deltaTime });

    s_MeshRenderer.Submit(s_Mesh);
}

void PlayState::OnDestroy() {

}