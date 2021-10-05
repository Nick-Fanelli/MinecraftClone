#include "Mesh.h"

void Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {

    if(m_VaoID != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

        return;
    }

    m_IndexCount = indices.size();

    glGenVertexArrays(1, &m_VaoID);
    glBindVertexArray(m_VaoID);

    glGenBuffers(1, &m_VboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_EboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TextureCoords));
}

Mesh::~Mesh() {
    if(m_VaoID == -1)
        return;

    glDeleteBuffers(1, &m_VboID);
    glDeleteBuffers(1, &m_EboID);
    glDeleteVertexArrays(1, &m_VaoID);
}