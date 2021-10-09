#pragma once

#include "pch.h"

class Shader {

public:
    Shader() = default;
    Shader(const Shader&) = default;

    Shader(const std::filesystem::path& vertexFilepath, const std::filesystem::path& fragmentFilepath);

    void Create();
    void Dispose();

    void Bind() const;

    void AddUniformMat4(const char* varName, const glm::mat4& mat4) const;
    void AddUniformVec3(const char* varName, const glm::vec3& vec) const;

    static void Unbind();

    operator bool() const { return m_ProgramID != -1; }

    ~Shader();

private:
    void AttachVertexShader(const std::string& source);
    void AttachFragmentShader(const std::string& source);

    void Link();

private:
    const std::filesystem::path m_VertexFilepath, m_FragmentFilepath;

    GLuint m_ProgramID = -1, m_VertexID, m_FragmentID;

};