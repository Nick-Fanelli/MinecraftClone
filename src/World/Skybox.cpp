#include "Skybox.h"

#include <stb_image.h>

#include "Render/Shader.h"
#include "Render/Camera.h"

static Shader s_SkyboxShader{ "res/shaders/Skybox.vert.glsl", "res/shaders/Skybox.frag.glsl" };

static float s_SkyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

void Skybox::Create() {
    if(m_TextureID != -1)
        return;

    if(!s_SkyboxShader)
        s_SkyboxShader.Create();

    glGenVertexArrays(1, &m_VaoID);
    glGenBuffers(1, &m_VboID);
    glBindVertexArray(m_VaoID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(s_SkyboxVertices), &s_SkyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

    int width, height, nrChannels;
    unsigned char* data;

    std::vector<std::string> faces = {
        "res/images/skybox/right.jpg",  
        "res/images/skybox/left.jpg",  
        "res/images/skybox/top.jpg",  
        "res/images/skybox/bottom.jpg",  
        "res/images/skybox/front.jpg",  
        "res/images/skybox/back.jpg"
    };

    for(uint32_t i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if(data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                            0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
}

void Skybox::Render() {

    glDepthFunc(GL_LEQUAL);

    s_SkyboxShader.Bind();
    s_SkyboxShader.AddUniformMat4("uViewProjection", Camera::GetRotatedViewMatrix());

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

    glBindVertexArray(m_VaoID);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    s_SkyboxShader.Unbind();

    glDepthFunc(GL_LESS);
}

Skybox::~Skybox() {
    if(m_TextureID == -1)
        return;

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDeleteTextures(1, &m_TextureID);

    glDeleteBuffers(1, &m_VaoID);
    glDeleteBuffers(1, &m_VboID);

    s_SkyboxShader.Dispose();
}