#pragma once

#include "Shader.h"
#include "Mesh.h"

class MeshRenderer {

public:

    MeshRenderer();

    void Create();

    void Submit(const Mesh& mesh);

private:
    static inline Shader s_Shader{ "res/shaders/Shader.vert.glsl", "res/shaders/Shader.frag.glsl" };

};