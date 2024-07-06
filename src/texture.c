#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <texture.h>
#include <glad/glad.h>
Pixel_Data* load_image( char * image_path){
    int width, height, nrChannels;
    Pixel_Data* data = stbi_load( image_path, &width, &height, &nrChannels, 0); 
    return data;
}
void clean_image(Pixel_Data* data){
    stbi_image_free(data);
}
void use_texture(Texture texture, int unit_offset){
    glActiveTexture(GL_TEXTURE0 + unit_offset);
    glBindTexture(GL_TEXTURE_2D, texture);
}

Texture create_texture(char* image_path,int unit_offset){
    Texture texture;
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    Pixel_Data* data = stbi_load( image_path, &width, &height, &nrChannels, 0); 

    glGenTextures(1,&texture);
    use_texture(texture, unit_offset);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {printf("HAHA ! YOU EVENT FAILED TO LOAD AN IMAGE? < %s >\n",image_path);}
    stbi_image_free(data);
    
    return  texture;
}
