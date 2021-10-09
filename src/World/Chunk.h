#pragma once

#include "pch.h"

#include "Block.h"

#include "Render/Mesh.h"

class Chunk {

public:

    Chunk() = default;

    void CreateChunk(int chunkX, int chunkY, int chunkZ);
    void UpdateChunkMesh();

public:
    const glm::vec3& GetChunkPosition() const { return m_ChunkPosition; }

    const Mesh& GetMesh() const { return m_Mesh; }

public:

    static constexpr int CHUNK_SIZE = 32;
    static constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
    static constexpr int CHUNK_VOLUME = CHUNK_AREA * CHUNK_SIZE;

private:
    void AddFace(std::vector<Vertex>* vertex, std::vector<uint32_t>* indices, const glm::vec3& first, const glm::vec3& second, const glm::vec3& third, const glm::vec3& fourth,
                 const glm::vec3& normal, const glm::vec2& texturePosition, bool shouldInvert);

private:
    glm::vec3 m_ChunkPosition;

    std::array<Block::Block*, CHUNK_VOLUME> m_Blocks;
    Mesh m_Mesh;

};