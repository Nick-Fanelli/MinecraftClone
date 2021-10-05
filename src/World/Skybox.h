#pragma once

#include "pch.h"

class Skybox {

public:
    Skybox() = default;
    Skybox(const Skybox&) = delete;

    void Create();

    void Render();

    ~Skybox();

private:
    GLuint m_VaoID, m_VboID;
    GLuint m_TextureID = -1;

};