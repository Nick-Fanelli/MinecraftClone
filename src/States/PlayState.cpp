#include "PlayState.h"

#include "Render/MeshRenderer.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

#include "World/Chunk.h"
#include "World/Skybox.h"

static MeshRenderer s_MeshRenderer;
static Chunk s_Chunk;

static Skybox s_Skybox;

void PlayState::OnCreate() {

    Block::InitializeBlockTextures();

    s_MeshRenderer.Create();
    s_Skybox.Create();

    s_Chunk.CreateChunk();

    Camera::SetPosition({ 0.0f, 32.0f, 3.0f});

}

void PlayState::OnUpdate(float deltaTime) {

    Camera::Update(deltaTime);

    s_MeshRenderer.Submit(s_Chunk.GetMesh(), Block::GetBlockSpritesheet());

    // Last
    s_Skybox.Render();
}

void PlayState::OnDestroy() {
    s_Skybox.~Skybox();
    Block::DestroyBlockTextures();
}