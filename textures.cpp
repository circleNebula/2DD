#include "stb_image.h"
#include "textures.h"
#include "GL/glu.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <iostream>


unsigned int* textures1;

using namespace std;

void textures::preLoadTexture(){
	textures1 =  (unsigned int*) calloc (20,sizeof(unsigned int));
    glGenTextures(20, textures1);
}
int textures::loadTexture(char filename[], int number)
{
 	
	
   // glGenTextures(number, &texture);
    glBindTexture(GL_TEXTURE_2D, textures1[number]); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
	
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    }else{
        std::cout << "Failed to load texture" << std::endl;
    }	
	stbi_image_free(data);
	
	return textures1[number];
}