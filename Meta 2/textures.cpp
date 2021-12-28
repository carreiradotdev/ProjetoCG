//
//  textures.c
//  projCG
//
//  Created by Francisco Carreira on 08/12/2021.
//

#include "textures.h"
#include "RgbImage.h"
#include <GLUT/Glut.h>

GLuint screenObj, skyboxObj, ipodObj;

void initTextures() {
    RgbImage img1;
    img1.LoadBmpFile("/Users/franciscocarreira/Desktop/CG/projCG/projCG/skybox.bmp");
    glGenTextures(1, &skyboxObj);
    glBindTexture(GL_TEXTURE_2D, skyboxObj);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,img1.GetNumCols(), img1.GetNumRows(),0, GL_RGB,GL_UNSIGNED_BYTE, img1.ImageData());
    
    RgbImage img2;
    img2.LoadBmpFile("/Users/franciscocarreira/Desktop/CG/projCG/projCG/ipod_ad1.bmp");
    glGenTextures(1, &ipodObj);
    glBindTexture(GL_TEXTURE_2D, ipodObj);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,img2.GetNumCols(), img2.GetNumRows(),0, GL_RGB,GL_UNSIGNED_BYTE, img2.ImageData());
    
    RgbImage img3;
    img3.LoadBmpFile("/Users/franciscocarreira/Desktop/CG/projCG/projCG/last.bmp");
    glGenTextures(1, &screenObj);
    glBindTexture(GL_TEXTURE_2D, screenObj);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,img3.GetNumCols(), img3.GetNumRows(),0, GL_RGB,GL_UNSIGNED_BYTE, img3.ImageData());
    
}
