#include "PlayState.h"

#include "../Render/MeshRenderer.h"
#include "../Render/Camera.h"

static MeshRenderer s_MeshRenderer;
static Mesh s_Mesh;

void PlayState::OnCreate() {

    s_MeshRenderer.Create();
    Camera::SetPosition({ 0.0f, 0.0f, 3.0f });

    s_Mesh.Create(
        {
        { { -0.5f, -0.5f, -0.5f, } },
         { { 0.5f, -0.5f, -0.5f, } },
         { { 0.5f,  0.5f, -0.5f, } },
         { { 0.5f,  0.5f, -0.5f, } },
        { { -0.5f,  0.5f, -0.5f, } },
        { { -0.5f, -0.5f, -0.5f, } },

        { { -0.5f, -0.5f,  0.5f, } },
         { { 0.5f, -0.5f,  0.5f, } },
         { { 0.5f,  0.5f,  0.5f, } },
         { { 0.5f,  0.5f,  0.5f, } },
        { { -0.5f,  0.5f,  0.5f, } },
        { { -0.5f, -0.5f,  0.5f, } },

        { { -0.5f,  0.5f,  0.5f, } },
        { { -0.5f,  0.5f, -0.5f, } },
        { { -0.5f, -0.5f, -0.5f, } },
        { { -0.5f, -0.5f, -0.5f, } },
        { { -0.5f, -0.5f,  0.5f, } },
        { { -0.5f,  0.5f,  0.5f, } },

         { { 0.5f,  0.5f,  0.5f, } },
         { { 0.5f,  0.5f, -0.5f, } },
         { { 0.5f, -0.5f, -0.5f, } },
         { { 0.5f, -0.5f, -0.5f, } },
         { { 0.5f, -0.5f,  0.5f, } },
         { { 0.5f,  0.5f,  0.5f, } },

        { { -0.5f, -0.5f, -0.5f, } },
         { { 0.5f, -0.5f, -0.5f, } },
         { { 0.5f, -0.5f,  0.5f, } },
         { { 0.5f, -0.5f,  0.5f, } },
        { { -0.5f, -0.5f,  0.5f, } },
        { { -0.5f, -0.5f, -0.5f, } },

        { { -0.5f,  0.5f, -0.5f, } },
         { { 0.5f,  0.5f, -0.5f, } },
         { { 0.5f,  0.5f,  0.5f, } },
         { { 0.5f,  0.5f,  0.5f, } },
        { { -0.5f,  0.5f,  0.5f, } },
        { { -0.5f,  0.5f, -0.5f, } },
        }, 
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35 }
    );

}

void PlayState::OnUpdate(float deltaTime) {
    s_MeshRenderer.Submit(s_Mesh);
}

void PlayState::OnDestroy() {

}