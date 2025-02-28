#include "texture.hpp"

unsigned int
LoadTexture(const char * filename, int width, int height)
{
    std::cerr << "Loading Texture \"" << filename << "\"...\r"; fflush(stderr);
    unsigned int texture;
    unsigned char * data;

    FILE * file;

    file = fopen(filename, "rb");

    if ( file == NULL ){
        std::cerr << "File Not Found !        " << std::endl; fflush(stderr);
        return 0;
    }
    data = (unsigned char *)malloc( width * height * 3 );

    fread( data, width * height * 3, 1, file );
    fclose( file );

    for(int i = 0; i < width * height ; ++i){
        int index = i*3;
        unsigned char B,R;
        B = data[index];
        R = data[index+2];

        data[index] = R;
        data[index+2] = B;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(
        GL_TEXTURE_ENV,
        GL_TEXTURE_ENV_MODE,
        GL_MODULATE
    );
    glTexParameterf(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_NEAREST
    );

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
    free(data);

    std::cout << "Texture \"" << filename << "\" Loaded and Exported To : " << texture << std::endl;
    return texture;
}