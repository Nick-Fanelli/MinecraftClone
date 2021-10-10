#include "ChunkManager.h"

#include "Render/MeshRenderer.h"

void ChunkManager::CreateChunk(int chunkX, int chunkZ) {
    auto chunkPtr = std::make_shared<Chunk>();
    chunkPtr->CreateChunk(chunkX, chunkZ);

    m_Chunks.push_back(chunkPtr);
}

void ChunkManager::RenderChunks(const Texture& spritesheet) {
    for(auto& chunk : m_Chunks) {
        MeshRenderer::Submit(chunk->GetMesh(), chunk->GetChunkPosition() * (float) Chunk::CHUNK_SIZE, spritesheet);
    }
}