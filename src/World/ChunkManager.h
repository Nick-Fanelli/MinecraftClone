#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include "pch.h"

#include "Chunk.h"

class ChunkManager {

public:
    ChunkManager() = default;
    ChunkManager(std::shared_ptr<Texture> blocksTextureAtlas);

    bool IsChunkCreated(int chunkX, int chunkZ);

    void SetChunks(const glm::vec2* chunkPositions, int chunkPositionsSize);

    void CreateChunk(int chunkX, int chunkZ);
    void UpdateChunks();
    void RenderChunks(std::shared_ptr<Texture> spritesheet);

    void RemoveChunk(int chunkX, int chunKZ);

    void ClearChunks();

private:
    std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> m_Chunks;

};