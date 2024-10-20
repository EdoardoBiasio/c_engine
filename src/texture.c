#include "texture.h"

texture_t* texture_create(const char* file_path) {
    i32 w, h, comp;
    u8* image = stbi_load(file_path, &w, &h, &comp, 0);
    if (!image) {
        berror("Unable to open image %s.", file_path);
    }
    binfo("Color channels: %d.", comp);
    
   
    texture_t* texture = bmalloc(sizeof(texture_t), M_TEXTURE);
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D),
    stbi_image_free(image);
    return texture;
}

void texture_destroy(texture_t* texture) {
    bfree(texture, sizeof(texture_t), M_TEXTURE);
}
