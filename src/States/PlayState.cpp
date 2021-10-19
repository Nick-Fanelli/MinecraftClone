#include "PlayState.h"

#include <FastNoiseLite.h>

#include "Render/MeshRenderer.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

#include "World/Chunk.h"
#include "World/Skybox.h"
#include "World/ChunkManager.h"
#include "World/Player.h"

static ChunkManager s_ChunkManager;

static Skybox s_Skybox;
static std::shared_ptr<Texture> s_BlockSpritesheet;

static bool s_Wireframe = false;

void PlayState::OnCreate() {

    s_BlockSpritesheet = std::make_shared<Texture>("res/images/blocks-texture-atlas.png");
    s_BlockSpritesheet->Create();

    s_ChunkManager = { s_BlockSpritesheet };

    MeshRenderer::OnInitialize();

    s_Skybox.Create();

    Player::Initialize(&s_ChunkManager);
    Player::SetPosition({ 0.0f, 255.0f, 0.0f });
    Camera::SetPosition(Player::GetPosition());

    // uint32_t worldSize = 10;

    // for(int x = 0; x < worldSize; x++) {
    //     for(int z = 0; z < worldSize; z++) {
    //         s_ChunkManager.CreateChunk(x, z);
    //     }
    // }

}

void PlayState::OnUpdate(float deltaTime) {

    Player::Update(deltaTime);

    s_ChunkManager.UpdateChunks();

    // Input
    if(s_Wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    s_ChunkManager.RenderChunks(s_BlockSpritesheet);

    if(s_Wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    s_Skybox.Render();
}

void PlayState::OnDestroy() {
    s_Skybox.~Skybox();
    s_BlockSpritesheet->Destroy();
}