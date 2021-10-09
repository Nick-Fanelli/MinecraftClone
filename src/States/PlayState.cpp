#include "PlayState.h"

#include "Render/MeshRenderer.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

#include "World/Chunk.h"
#include "World/Skybox.h"
#include "World/ChunkManager.h"

static Skybox s_Skybox;
static ChunkManager s_ChunkManager;

void PlayState::OnCreate() {

    Block::InitializeBlockTextures();
    MeshRenderer::OnInitialize();

    s_Skybox.Create();

    Camera::SetPosition({ 0.0f, 32.0f, 3.0f});

    for(int x = 0; x < 10; x++) {
        for(int y = 0; y < 10; y++) {
            s_ChunkManager.CreateChunk(x, 0.0f, y);
        }
    }

}

void PlayState::OnUpdate(float deltaTime) {

    Camera::Update(deltaTime);

    s_ChunkManager.RenderChunks(Block::GetBlockSpritesheet());

    s_Skybox.Render();
}

void PlayState::OnDestroy() {
    s_Skybox.~Skybox();
    Block::DestroyBlockTextures();
}