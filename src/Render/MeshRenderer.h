#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

class MeshRenderer {

public:

    MeshRenderer();

    void Create();

    void Submit(const Mesh& mesh);
    void Submit(const Mesh& mesh, const Texture& texture);

private:
    static inline Shader s_Shader{ "res/shaders/Shader.vert.glsl", "res/shaders/Shader.frag.glsl" };

};