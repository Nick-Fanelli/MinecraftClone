#include "ChunkManager.h"

#include <future>
#include <mutex>

#include "Render/MeshRenderer.h"

static std::mutex s_ChunksMutex;
static std::vector<std::future<void>> s_LoadChunkFutures;

static void LoadChunk(std::unordered_map<glm::vec2, std::shared_ptr<Chunk>>* chunks, int chunkX, int chunkZ) {
    auto chunkPtr = std::make_shared<Chunk>();

    chunkPtr->CreateChunk(chunkX, chunkZ);

    std::lock_guard<std::mutex> lock(s_ChunksMutex);
    (*chunks)[{chunkX, chunkZ}] = chunkPtr;
}

bool ChunkManager::IsChunkCreated(int chunkX, int chunkZ) {
    return s_Chunks.find({chunkX, chunkZ}) != s_Chunks.end();
}

void ChunkManager::CreateChunk(int chunkX, int chunkZ) {
    if(IsChunkCreated(chunkX, chunkZ))
        return;

    s_LoadChunkFutures.push_back(std::async(std::launch::async, LoadChunk, &s_Chunks, chunkX, chunkZ));
}

void ChunkManager::RenderChunks(const Texture& spritesheet) {

    static bool createdChunk = false;
    createdChunk = false;

    for(auto& chunk : s_Chunks) {
        if(chunk.second->GetMesh().IsCreated())
            MeshRenderer::Submit(chunk.second->GetMesh(), chunk.second->GetChunkPosition() * (float) Chunk::CHUNK_SIZE, spritesheet);
        else {
            chunk.second->UpdateChunkMesh();
            createdChunk = true;
        }
    }
}