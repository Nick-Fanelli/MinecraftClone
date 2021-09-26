#pragma once

#include "pch.h"

class Shader {

public:
    Shader() = default;
    Shader(const Shader&) = delete;

    Shader(const std::filesystem::path& vertexFilepath, const std::filesystem::path& fragmentFilepath);

    void Create();
    void Dispose();

    void Bind() const;

    static void Unbind();

    ~Shader();

private:
    void AttachVertexShader(const std::string& source);
    void AttachFragmentShader(const std::string& source);

    void Link();

private:
    const std::filesystem::path m_VertexFilepath, m_FragmentFilepath;

    GLuint m_ProgramID = -1, m_VertexID, m_FragmentID;

};