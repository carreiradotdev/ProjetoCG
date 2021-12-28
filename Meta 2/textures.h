//
//  textures.h
//  projCG
//
//  Created by Francisco Carreira on 08/12/2021.
//

#ifndef textures_h
#define textures_h

#include <stdio.h>
#include <GLUT/Glut.h>

static GLfloat textures[] = {
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0
};

extern GLuint skyboxObj, screenObj, ipodObj;

void initTextures();

#endif /* textures_h */
