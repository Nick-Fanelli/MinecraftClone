#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Texture::Create() {
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    // Setup Image Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int channels;

    unsigned char* data = stbi_load(m_Filepath.string().c_str(), &m_Width, &m_Height, &channels, 0);

    if(data != nullptr) {
        if (channels == 3) { // RGB Channels
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (channels == 4) { // RBGA Channels
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "ERROR: Unknown number of channels" << std::endl;
        }

        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::Destroy() {

    if(m_TextureID == -1)
        return;

    glDeleteTextures(1, &m_TextureID);
}