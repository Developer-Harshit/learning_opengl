#ifndef TEXTURE_H
#define TEXTURE_H
#define TEXTURE_PATH "resources/textures/"
typedef unsigned int Texture;
typedef  unsigned char Pixel_Data;
Pixel_Data* load_image(char*);
void clean_image(Pixel_Data*);
void use_texture(Texture, int);
Texture create_texture(char* ,int);
#endif 