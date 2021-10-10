#pragma once

#include "pch.h"

#include "Chunk.h"

class ChunkManager {

public:
    ChunkManager() = default;
    ChunkManager(const ChunkManager&) = delete;

    void CreateChunk(int chunkX, int chunkZ);
    
    void RenderChunks(const Texture& spritesheet);

private:
    std::vector<std::shared_ptr<Chunk>> m_Chunks;

};