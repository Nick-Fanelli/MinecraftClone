#include "ChunkManager.h"

#include <thread>
#include <mutex>

#include "Render/MeshRenderer.h"

static std::mutex s_ChunksMutex;

static void LoadChunk(std::unordered_map<glm::vec2, std::shared_ptr<Chunk>>* chunks, int chunkX, int chunkZ) {
    auto chunkPtr = std::make_shared<Chunk>();

    chunkPtr->CreateChunk(chunkX, chunkZ);

    std::lock_guard<std::mutex> lock(s_ChunksMutex);
    (*chunks)[{chunkX, chunkZ}] = chunkPtr;
}

bool ChunkManager::IsChunkCreated(int chunkX, int chunkZ) {
    return m_Chunks.find({chunkX, chunkZ}) != m_Chunks.end();
}

ChunkManager::ChunkManager(std::shared_ptr<Texture> blocksTextureAtlas) {
    Chunk::s_BlocksTextureAtlas = blocksTextureAtlas;
}

void ChunkManager::CreateChunk(int chunkX, int chunkZ) {
    if(IsChunkCreated(chunkX, chunkZ))
        return;

    m_Chunks[{chunkX, chunkZ}] = std::make_shared<Chunk>(); // Allocate something

    std::thread{LoadChunk, &m_Chunks, chunkX, chunkZ}.detach();
}

void ChunkManager::SetChunks(const glm::vec2* chunkPositions, int chunkPositionsSize) {
    for (int i = 0; i < chunkPositionsSize; i++) {
        CreateChunk(chunkPositions[i].x, chunkPositions[i].y);
    }

    std::vector<glm::vec2> chunksToErase;

    for (auto& chunk : m_Chunks) {
        bool isSafe = false;

        for (int i = 0; i < chunkPositionsSize; i++) {
            if (chunkPositions[i] == chunk.first) {
                isSafe = true;
                break;
            }
        }

        if (!isSafe)
            chunksToErase.push_back(chunk.first);
    }

    for (auto& erase : chunksToErase) {
        m_Chunks.erase(erase);
    }
}

void ChunkManager::RemoveChunk(int chunkX, int chunkZ) {
    if (!IsChunkCreated(chunkX, chunkZ))
        return;

    m_Chunks[{chunkX, chunkZ}] = nullptr;
}

void ChunkManager::ClearChunks() {
    m_Chunks.clear();
}

void ChunkManager::UpdateChunks() {
    for(auto& chunk : m_Chunks) {
        if(chunk.second->m_ShouldCreateChunkMesh)
            chunk.second->CreateMesh();
    }
}

void ChunkManager::RenderChunks(std::shared_ptr<Texture> spritesheet) {

    static bool createdChunk = false;
    createdChunk = false;

    for(auto& chunk : m_Chunks) {
        if(chunk.second->GetMesh().IsCreated())
            MeshRenderer::Submit(chunk.second->GetMesh(), chunk.second->GetChunkPosition() * (float) Chunk::CHUNK_SIZE, spritesheet);
    }
}