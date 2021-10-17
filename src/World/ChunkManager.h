#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include "pch.h"

#include "Chunk.h"

class ChunkManager {

public:
    ChunkManager() = delete;
    ~ChunkManager() = delete; 

    static bool IsChunkCreated(int chunkX, int chunkZ);

    static void CreateChunk(int chunkX, int chunkZ);
    static void UpdateChunks();
    static void RenderChunks(const Texture& spritesheet);

private:
    static inline std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> s_Chunks;

};