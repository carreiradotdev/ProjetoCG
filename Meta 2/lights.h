//
//  lights.h
//  projCG
//
//  Created by Francisco Carreira on 08/12/2021.
//

#ifndef lights_h
#define lights_h

#include <stdio.h>
#include <GLUT/Glut.h>

GLfloat dicR = 0, dicG = 0, dicB = 0;

struct {
    GLfloat intensity = 1;
    GLfloat color[3] = { 1,1,1 };
    GLfloat position[4] = { 0, 15, 0, 1 };
    GLfloat ambient[4] = { 0, 0, 0, 0 };
    GLfloat diffuse[4] = { 1, 1, 1, 1 };
    GLfloat specular[4] = { 1, 1, 1, 1 };
    GLfloat direction[3] = { 0, -1, 0 };
    GLint cutoff = 15;
    GLint exponent = 20;
} spotLight;

struct {
    GLfloat intensity = 0.2;
    GLfloat color[3] = { 0.8,0.8,0.8 };
    GLfloat position[4] = { 0, 0, 1, 0 };
    GLfloat ambient[4] = { 0, 0, 0, 0 };
    GLfloat diffuse[4] = { 1, 1, 1, 1 };
    GLfloat specular[4] = { 1, 1, 1, 1 };
    GLfloat direction[3] = { 0, -1, 0 };
} directionLight;

void initLights(void);

#endif /* lights_h */
