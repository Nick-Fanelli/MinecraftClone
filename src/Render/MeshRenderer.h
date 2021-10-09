#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

class MeshRenderer {

public:

    MeshRenderer() = delete;

    static void OnInitialize();

    static void Submit(const Mesh& mesh);
    static void Submit(const Mesh& mesh, const Texture& texture);
    static void Submit(const Mesh& mesh, const glm::vec3& transformation, const Texture& texture);

private:
    static inline Shader s_Shader{ "res/shaders/Shader.vert.glsl", "res/shaders/Shader.frag.glsl" };

};