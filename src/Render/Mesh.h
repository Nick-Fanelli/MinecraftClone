#pragma once

#include "pch.h"

#include "Vertex.h"

class MeshRenderer;

struct Mesh {

    Mesh() = default;

    void Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    inline bool IsCreated() const { return m_VaoID != -1; }

    ~Mesh();

private:
    GLuint m_VaoID = -1, m_VboID = -1, m_EboID = -1;

    size_t m_IndexCount = 0; 

    friend class MeshRenderer;

};