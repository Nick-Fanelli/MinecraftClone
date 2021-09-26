#include "PlayState.h"

#include "../Render/MeshRenderer.h"

static MeshRenderer s_MeshRenderer;
static Mesh s_Mesh;

void PlayState::OnCreate() {

    s_MeshRenderer.Create();

    s_Mesh.Create(
        {
            { { 0.5f, 0.5f, 0.0f } },
            { { -0.5f, 0.5f, 0.0f } },
            { { -0.5f, -0.5f, 0.0f } },
            { { 0.5f, -0.5f, 0.0f } }
        }, 
        { 0, 1, 2, 0, 2, 3 }
    );

}

void PlayState::OnUpdate(float deltaTime) {
    s_MeshRenderer.Submit(s_Mesh);
}

void PlayState::OnDestroy() {

}