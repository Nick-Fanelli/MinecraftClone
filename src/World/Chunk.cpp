#include "Chunk.h"

#include "Render/Vertex.h"

void Chunk::CreateChunk() {
    for(auto& block : m_Blocks) {
        block = Block::BlockType::GRASS;
    }

    UpdateChunkMesh();
}

static int GetBlockArrayIndex(int x, int y, int z) {
    return (z * Chunk::CHUNK_AREA) + (y * Chunk::CHUNK_SIZE) + x;
}

static glm::vec3 GetBlockPosition(int index) {
    const int z = index / (Chunk::CHUNK_AREA);
    index -= (z * Chunk::CHUNK_AREA);

    const int y = index / Chunk::CHUNK_SIZE;
    const int x = index % Chunk::CHUNK_SIZE;

    return { x, y, z };
}

static bool IsBlockInBounds(const glm::vec3& position) {
    return position.x >= 0 && position.y >= 0 && position.z >= 0 && 
           position.x < Chunk::CHUNK_SIZE && position.y < Chunk::CHUNK_SIZE && position.z < Chunk::CHUNK_SIZE;
}

void Chunk::AddFace(std::vector<Vertex>* vertices, std::vector<uint32_t>* indices, const glm::vec3& first, const glm::vec3& second, const glm::vec3& third, const glm::vec3& fourth) {
    vertices->push_back({ first, { 0.0f, 0.0f, 1.0f } });
    vertices->push_back({ second, { 0.0f, 0.0f, 1.0f } });
    vertices->push_back({ third, { 0.0f, 0.0f, 1.0f } });
    vertices->push_back({ fourth, { 0.0f, 0.0f, 1.0f } });

    uint32_t startingValue = indices->size() > 0 ? ((indices->back()) + 1) : 0;

    indices->push_back(startingValue);
    indices->push_back(startingValue + 1);
    indices->push_back(startingValue + 2);
    indices->push_back(startingValue);
    indices->push_back(startingValue + 2);
    indices->push_back(startingValue + 3);
}

void Chunk::UpdateChunkMesh() {

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for(uint32_t i = 0; i < m_Blocks.size(); i++) {

        auto blockPosition = GetBlockPosition(i);        

        glm::vec3 frontNeighbor = { blockPosition.x, blockPosition.y, blockPosition.z - 1.0f };

        if(IsBlockInBounds(frontNeighbor)) {

        } else {
        // Front Face
        AddFace(&vertices, &indices, 
            { blockPosition.x - 0.5f, blockPosition.y - 0.5f, blockPosition.z },
            { blockPosition.x - 0.5f, blockPosition.y + 0.5f, blockPosition.z },
            { blockPosition.x + 0.5f, blockPosition.y + 0.5f, blockPosition.z },
            { blockPosition.x + 0.5f, blockPosition.y - 0.5f, blockPosition.z });
        }

    }

    m_Mesh.Create(vertices, indices);

}
