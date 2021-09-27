#include "PlayState.h"

#include "Render/MeshRenderer.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

static MeshRenderer s_MeshRenderer;
static Mesh s_Mesh;

static Texture s_Texture;

void PlayState::OnCreate() {

    s_MeshRenderer.Create();
    // Camera::SetPosition({ 0.0f, 0.0f, 2.0f });

    s_Texture = { "res/images/texture-atlas.png" };
    s_Texture.Create();

    float min = 0.0f;
    float max = 16.0f / 256.0f;

    s_Mesh.Create(
        {
            // Front
            { { 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { max, min }, (float) s_Texture.GetTextureID() },
            { { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { min, min }, (float) s_Texture.GetTextureID() },
            { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { min, max }, (float) s_Texture.GetTextureID() },
            { { 0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { max, max }, (float) s_Texture.GetTextureID() },
        }, 
        {
            // Front
            0, 1, 2, 
            2, 3, 0,
        }
    );

}

void PlayState::OnUpdate(float deltaTime) {

    Camera::Update(deltaTime);

    s_MeshRenderer.Submit(s_Mesh, s_Texture);
}

void PlayState::OnDestroy() {
    s_Texture.Destroy();
    s_Mesh.~Mesh();
}