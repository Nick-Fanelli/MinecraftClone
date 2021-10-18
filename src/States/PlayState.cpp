#include "PlayState.h"

#include <FastNoiseLite.h>

#include "Render/MeshRenderer.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

#include "World/Chunk.h"
#include "World/Skybox.h"
#include "World/ChunkManager.h"
#include "World/Player.h"

static Skybox s_Skybox;

static bool s_Wireframe = false;

void PlayState::OnCreate() {

    Block::InitializeBlockTextures();
    MeshRenderer::OnInitialize();

    s_Skybox.Create();

    Player::SetPosition({ 0.0f, 255.0f, 0.0f });
    Camera::SetPosition(Player::GetPosition());

    uint32_t worldSize = 10;

    for(int x = 0; x < worldSize; x++) {
        for(int z = 0; z < worldSize; z++) {
            ChunkManager::CreateChunk(x, z);
        }
    }

}

void PlayState::OnUpdate(float deltaTime) {

    Player::Update(deltaTime);

    ChunkManager::UpdateChunks();

    // Input
    if(s_Wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    ChunkManager::RenderChunks(Block::GetBlockSpritesheet());

    if(s_Wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    s_Skybox.Render();
}

void PlayState::OnDestroy() {
    s_Skybox.~Skybox();
    Block::DestroyBlockTextures();
}