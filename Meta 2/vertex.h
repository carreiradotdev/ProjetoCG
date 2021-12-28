//
//  vertex.h
//  projCG
//
//  Created by Francisco Carreira on 11/11/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GLUT/glut.h>

#ifndef vertex_h
#define vertex_h

const GLfloat size = 0.5;

const GLfloat vertex[] = {
    // Front
    -size,   size,  size,    // 0
    -size,  -size,  size,    // 1
    size,  -size,  size,    // 2
    size,   size,  size,    // 3
    // Right
    size,   size,  size,    // 4
    size,  -size,  size,    // 5
    size,  -size, -size,    // 6
    size,   size, -size,    // 7
    // Up
    size,  size, -size,    // 8
    -size,  size, -size,    // 9
    -size,  size,  size,    // 10
    size,  size,  size,    // 11
    // Back
    -size,   size, -size,    // 12
    size,   size, -size,    // 13
    size,  -size, -size,    // 14
    -size,  -size, -size,    // 15
    // Left
    -size,   size,  size,    // 16
    -size,   size, -size,    // 17
    -size,  -size, -size,    // 18
    -size,  -size,  size,    // 19
    // Lower
    -size,  -size,  size,    // 20
    -size,  -size, -size,    // 21
    size,  -size, -size,    // 22
    size,  -size,  size,    // 23
};

#endif /* vertex_h */
