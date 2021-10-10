#include "PlayState.h"

#include "Render/MeshRenderer.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

#include "World/Chunk.h"
#include "World/Skybox.h"
#include "World/ChunkManager.h"

static Skybox s_Skybox;
static ChunkManager s_ChunkManager;

static bool s_Wireframe = true;

void PlayState::OnCreate() {

    Block::InitializeBlockTextures();
    MeshRenderer::OnInitialize();

    s_Skybox.Create();

    Camera::SetPosition({ 0.0f, 32.0f, 3.0f});

    // s_ChunkManager.CreateChunk(0, 0, 0);

    uint32_t worldSize = 2;

    for(int x = 0; x < worldSize; x++) {
        for(int z = 0; z < worldSize; z++) {
            s_ChunkManager.CreateChunk(x, z);
        }
    }

}

void PlayState::OnUpdate(float deltaTime) {

    Camera::Update(deltaTime);

    // Input
    if(s_Wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    s_ChunkManager.RenderChunks(Block::GetBlockSpritesheet());

    if(s_Wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    s_Skybox.Render();
}

void PlayState::OnDestroy() {
    s_Skybox.~Skybox();
    Block::DestroyBlockTextures();
}