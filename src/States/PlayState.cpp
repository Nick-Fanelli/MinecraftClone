#include "PlayState.h"

#include "Render/MeshRenderer.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

#include "World/Chunk.h"

static MeshRenderer s_MeshRenderer;
static Chunk s_Chunk;

void PlayState::OnCreate() {

    InitializeBlockTextures();

    s_MeshRenderer.Create();

    s_Chunk.CreateChunk();

    Camera::SetPosition({ 0.0f, 17.0f, 3.0f});

}

void PlayState::OnUpdate(float deltaTime) {

    Camera::Update(deltaTime);

    s_MeshRenderer.Submit(s_Chunk.GetMesh(), GetBlockSpritesheet());

}

void PlayState::OnDestroy() {
    DestroyBlockTextures();
}