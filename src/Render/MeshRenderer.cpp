#include "MeshRenderer.h"

#include "Camera.h"

MeshRenderer::MeshRenderer() {
}

void MeshRenderer::Create() {
    if(!s_Shader)
        s_Shader.Create();
}

void MeshRenderer::Submit(const Mesh& mesh) {

    s_Shader.Bind();
    s_Shader.AddUniformMat4("uViewProjection", Camera::GetViewProjection());

    glBindVertexArray(mesh.m_VaoID);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_VboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_EboID);

    glDrawElements(GL_TRIANGLES, mesh.m_IndexCount, GL_UNSIGNED_INT, (void*) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);

    glBindVertexArray(0);

    Shader::Unbind();

}