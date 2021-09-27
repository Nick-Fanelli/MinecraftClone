#pragma once

#include "pch.h"

class Texture {

public:

    Texture() = default;
    Texture(const std::filesystem::path& filepath) : m_Filepath(filepath) {}

    void Create();
    void Destroy();

    inline void Bind() { 
        if(m_TextureID != -1)
            glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    const GLuint GetTextureID() const { return m_TextureID; }

    ~Texture() { Destroy(); }

private:
    std::filesystem::path m_Filepath;

    GLuint m_TextureID = -1;
    int m_Width, m_Height;

};