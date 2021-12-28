//
//  normals.h
//  projCG
//
//  Created by Francisco Carreira on 11/11/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GLUT/glut.h>

#ifndef normals_h
#define normals_h

const GLfloat normal[] = {
    // Front
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    // Right
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    // Up
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    // Back
    0.0,  0.0, -1.0,
    0.0,  0.0, -1.0,
    0.0,  0.0, -1.0,
    0.0,  0.0, -1.0,
    // Left
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    // Down
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
};

#endif /* normals_h */
